-- SDMP: SurrounDead fan multiplayer mod (UE4SS Lua)
-- Main menu gets "MP: HOST" and "MP: JOIN <ip>" entries. Keys as backup: F7 host, F9 join, F6 status.
-- Console: sdmp_host, sdmp_join <SteamID64>, sdmp_join_ip <ip>, sdmp_status, sdmp_spawn, sdmp_levels
-- Log: <Win64>/SDMP.log
--
-- THREADING RULE: UE4SS runs ExecuteWithDelay / LoopAsync callbacks on its own thread, and frees finished
-- ExecuteWithDelay callbacks from a background GC ("Freed invalid callbacks"). Combining ExecuteWithDelay with
-- ExecuteInGameThread crashed the game inside UE4SS about 20s after launch (1 in 3 launches). So this file uses
-- exactly ONE LoopAsync, which once per second runs a tiny scheduler on the game thread. Nothing else is async.

local UEHelpers = require("UEHelpers")
local VERSION = "0.2.0"
local LEVEL_NAME = "LongdownValley"
local PLAYER_CLASS = "/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C"

local logf = io.open("SDMP.log", "a")
local function log(s)
  local line = os.date("%Y-%m-%d %H:%M:%S ") .. s
  print("[SDMP] " .. s .. "\n")
  if logf then logf:write(line, "\n"); logf:flush() end
end

local state = { hosting = false, joining = false, target = nil, spawned = {} }
local menuUI = { host = nil, join = nil, menu = nil }
local setButtonText, cmdHost, cmdJoin, restoreHostControl   -- defined later

-- ---------- scheduler (all game-thread work goes through here) ----------
local tasks = {}   -- { at = time, every = seconds|nil, fn = function, name = string, cancelled = bool }
local function after(seconds, fn, name) local t = { at = os.time() + seconds, fn = fn, name = name or "?" }; tasks[#tasks+1] = t; return t end
local function every(seconds, fn, name) local t = { at = os.time() + seconds, every = seconds, fn = fn, name = name or "?" }; tasks[#tasks+1] = t; return t end
local function cancel(t) if t then t.cancelled = true end end
local function runDueTasks()
  local now = os.time()
  local keep = {}
  for _, t in ipairs(tasks) do
    if not t.cancelled then
      if now >= t.at then
        local ok, err = pcall(t.fn)
        if not ok then log("task '" .. t.name .. "' error: " .. tostring(err)) end
        if t.every and not t.cancelled then t.at = now + t.every; keep[#keep+1] = t end
      else
        keep[#keep+1] = t
      end
    end
  end
  tasks = keep
end
LoopAsync(1000, function()
  ExecuteInGameThread(function() local ok, err = pcall(runDueTasks); if not ok then print("[SDMP] scheduler error: " .. tostring(err) .. "\n") end end)
  return false
end)

-- ---------- config ----------
local function readConfig()
  local cfg = {}
  local dir = debug.getinfo(1, "S").source:match("^@?(.*[\\/])") or ""
  local f = io.open(dir .. "sdmp.ini", "r")
  if not f then return cfg end
  for line in f:lines() do
    local k, v = line:match("^%s*([%w_]+)%s*=%s*(.-)%s*$")
    if k and v and v ~= "" and line:sub(1, 1) ~= ";" then cfg[k] = v end
  end
  f:close()
  return cfg
end

-- ---------- helpers ----------
local function valid(o) return o ~= nil and o:IsValid() end
local function short(o) return valid(o) and o:GetFullName():gsub("^%S+ ", "") or "nil" end

local function consoleCmd(cmd)
  local pc = UEHelpers.GetPlayerController()
  UEHelpers.GetKismetSystemLibrary():ExecuteConsoleCommand(UEHelpers.GetWorld(), cmd, pc)
end

local function netDriver()
  local ok, nd = pcall(function() return UEHelpers.GetWorld().NetDriver end)
  if ok and valid(nd) then return nd end
  return nil
end

local function isClient()
  local nd = netDriver()
  if not nd then return false end
  local ok, sc = pcall(function() return nd.ServerConnection end)
  return ok and valid(sc)
end

local function liveInstances(className)
  local res = {}
  local objs = FindAllOf(className)
  if objs then for _, o in ipairs(objs) do
    if valid(o) and not o:GetFullName():find("Default__", 1, true) then res[#res+1] = o end
  end end
  return res
end

local function status(tag)
  local s = "STATUS" .. (tag and ("[" .. tag .. "]") or "")
  pcall(function() s = s .. " world=" .. short(UEHelpers.GetWorld()) end)
  local nd = netDriver()
  s = s .. " driver=" .. (nd and short(nd) or "nil") .. " role=" .. (nd and (isClient() and "CLIENT" or "SERVER") or "standalone")
  pcall(function() s = s .. " pawn=" .. short(UEHelpers.GetPlayerController().Pawn) end)
  pcall(function() s = s .. " players=" .. tostring(#UEHelpers.GetGameStateBase().PlayerArray) end)
  local conns = liveInstances("NetConnection")
  s = s .. " connections=" .. #conns
  for _, c in ipairs(conns) do
    local lrt, chans, drv = "?", "?", "?"
    pcall(function() lrt = string.format("%.1f", c.LastReceiveTime) end)
    pcall(function() chans = tostring(#c.OpenChannels) end)
    pcall(function() local d = c.Driver; drv = valid(d) and d:GetClass():GetFName():ToString() or "nil" end)
    s = s .. " [" .. c:GetClass():GetFName():ToString() .. " lastRecv=" .. lrt .. " channels=" .. chans .. " driver=" .. drv .. "]"
  end
  s = s .. " controllers=" .. #liveInstances("BP_PlayerController_C") .. " playerpawns=" .. #liveInstances("BP_PlayerCharacter_C")
  s = s .. " corrections=" .. tostring(state.adjusts or 0)
  for _, p in ipairs(liveInstances("BP_PlayerCharacter_C")) do
    pcall(function() s = s .. string.format(" [%s walk=%.0f role=%s]", p:GetFName():ToString():gsub("BP_PlayerCharacter_C_", "#"), p.CharacterMovement.MaxWalkSpeed, tostring(p:GetLocalRole())) end)
  end
  log(s)
  return s
end

-- ---------- host side: spawn pawns for joined players ----------
-- spawn method: "rpc" = ask the game's own controller respawn (Svr_RequestRespawn_Random, written by the dev as a
-- server RPC); "spawn" = generic SpawnActor + Possess (bare body, no game setup). Env SDMP_SPAWN or sdmp.ini spawn_method.
local function spawnMethod()
  -- NOTE: "rpc" was tested and rejected: the game's Survival_Respawn is hard-wired to player controller 0,
  -- so a remote controller's request respawns/resets the HOST instead. Default is the generic spawn.
  local m = os.getenv("SDMP_SPAWN") or readConfig().spawn_method or "spawn"
  return m
end

local function spawnFor(pc)
  if spawnMethod() == "rpc" then
    local ok, err = pcall(function() pc:Svr_RequestRespawn_Random() end)
    log(string.format("spawnFor(rpc): Svr_RequestRespawn_Random on %s ok=%s %s", short(pc), tostring(ok), ok and "" or tostring(err)))
    return ok
  end
  local world = UEHelpers.GetWorld()
  local cls = StaticFindObject(PLAYER_CLASS)
  if not valid(cls) then log("spawnFor: player class not found"); return false end
  local g = state.lastGood or { X = 0, Y = 0, Z = 300 }
  local loc = { X = g.X + 250, Y = g.Y + 250, Z = g.Z + 100 }
  local ok, pawn = pcall(function() return world:SpawnActor(cls, loc, { Pitch = 0, Yaw = 0, Roll = 0 }) end)
  if not ok or not valid(pawn) then log("spawnFor: SpawnActor failed: " .. tostring(pawn)); return false end
  -- copy movement tuning from the host's (game-initialised) pawn so client prediction and server agree
  pcall(function()
    local hp = UEHelpers.GetPlayerController().Pawn
    if not valid(hp) then return end
    local src, dst = hp.CharacterMovement, pawn.CharacterMovement
    local diffs = {}
    for _, p in ipairs({ "MaxWalkSpeed", "MaxWalkSpeedCrouched", "MaxAcceleration", "BrakingDecelerationWalking", "GroundFriction", "JumpZVelocity", "GravityScale", "NetworkSmoothingMode", "NetworkSimulatedSmoothLocationTime", "NetworkSimulatedSmoothRotationTime", "ListenServerNetworkSimulatedSmoothLocationTime", "ListenServerNetworkSimulatedSmoothRotationTime", "NetworkMaxSmoothUpdateDistance", "NetworkNoSmoothUpdateDistance", "bOrientRotationToMovement", "bUseControllerDesiredRotation", "bNetworkSkipProxyPredictionOnNetUpdate" }) do
      pcall(function()
        local a, b = src[p], dst[p]
        if tostring(a) ~= tostring(b) then diffs[#diffs+1] = p .. ":" .. tostring(b) .. "->" .. tostring(a); dst[p] = a end
      end)
    end
    for _, p in ipairs({ "bUseControllerRotationYaw", "bUseControllerRotationPitch", "NetUpdateFrequency", "MinNetUpdateFrequency", "NetPriority" }) do
      pcall(function() local a, b = hp[p], pawn[p]; if tostring(a) ~= tostring(b) then diffs[#diffs+1] = p .. ":" .. tostring(b) .. "->" .. tostring(a); pawn[p] = a end end)
    end
    log("spawnFor: movement/net settings copied from host pawn (" .. #diffs .. " differed): " .. table.concat(diffs, " "))
  end)
  -- (client-authoritative movement is enabled later by ensureSmoothing, once the joiner has the world loaded;
  -- doing it at spawn let a client that hadn't streamed the level yet fall through the floor and drag the server copy with it)
  local ok2, err = pcall(function() pc:Possess(pawn) end)
  log(string.format("spawnFor: spawned %s for %s possess_ok=%s %s", short(pawn), short(pc), tostring(ok2), ok2 and "" or tostring(err)))
  return ok2
end

local function updateHostStatusLabel()
  if valid(menuUI.status) then
    local n = 0; pcall(function() n = #UEHelpers.GetGameStateBase().PlayerArray end)
    setButtonText(menuUI.status, "MP: HOSTING OK - players: " .. n .. " - click New or Load")
  end
end

local function spawnMissing()
  if isClient() then return end
  updateHostStatusLabel()
  local hostPc = UEHelpers.GetPlayerController()
  local okh, hostPawn = pcall(function() return hostPc.Pawn end)
  -- remember the last place the host stood on solid ground; joiners spawn there even if the host is dead right now
  if okh and valid(hostPawn) then
    pcall(function()
      local l, v = hostPawn:K2_GetActorLocation(), hostPawn:GetVelocity()
      local dead = false; pcall(function() dead = hostPawn["PlayerDead?"] == true end)
      if math.abs(v.Z) < 50 and not (math.abs(l.X) < 1 and math.abs(l.Y) < 1) and not dead then state.lastGood = { X = l.X, Y = l.Y, Z = l.Z } end
    end)
  end
  if not state.lastGood then return end  -- host has not stood anywhere yet
  for _, pc in ipairs(liveInstances("BP_PlayerController_C")) do
    if pc:GetAddress() ~= hostPc:GetAddress() then
      local okp, pawn = pcall(function() return pc.Pawn end)
      -- a dead body still counts as "no pawn": the game's own respawn flow is hard-wired to the host, so we
      -- respawn joined players ourselves ~6s after death (unpossess the corpse, spawn a fresh body)
      if okp and valid(pawn) then
        local dead = false; pcall(function() dead = pawn["PlayerDead?"] == true end)
        if not dead and state.deadPawns and state.deadPawns[pawn:GetAddress()] then dead = true end
        if dead then
          local key = pc:GetFullName()
          state.deadSince = state.deadSince or {}
          state.deadSince[key] = state.deadSince[key] or os.time()
          if os.time() - state.deadSince[key] >= 6 then
            log("joined player is dead, respawning: " .. key)
            pcall(function() pc:UnPossess() end)
            state.deadSince[key] = nil
            state.spawned[key] = nil
            pawn = nil
          end
        end
      end
      if not (okp and valid(pawn)) then
        local key = pc:GetFullName()
        -- allow a retry every 10s (covers death without respawn, and the rpc path not producing a pawn)
        if not state.spawned[key] or os.time() - state.spawned[key] >= 10 then
          log("joined player without pawn: " .. key)
          if spawnFor(pc) then state.spawned[key] = os.time() end
        end
      end
    end
  end
end

-- ---------- streaming levels ----------
local function eachStreamingLevel(fn)
  local world = UEHelpers.GetWorld()
  local ok, levels = pcall(function() return world.StreamingLevels end)
  if not ok or not levels then return end
  levels:ForEach(function(i, el)
    local ls = el:get()
    if valid(ls) then
      local function try(f, dflt) local ok2, v = pcall(f); if ok2 then return v end; return dflt end
      local pkg = try(function() local lvl = ls:GetLoadedLevel(); if valid(lvl) then return lvl:GetOuter():GetFullName():gsub("^Package ", "") end; return "?" end, "?")
      if pkg == "?" or pkg == "None" then pkg = ls:GetFullName():gsub("^.*:", "") end
      local loaded = try(function() return ls:IsLevelLoaded() end, false)
      local visible = try(function() return ls:IsLevelVisible() end, false)
      fn(ls, pkg, loaded == true, visible == true)
    end
  end)
end

local function logLevels(tag)
  eachStreamingLevel(function(ls, pkg, loaded, visible)
    log(string.format("LEVELS[%s] %s loaded=%s visible=%s", tag, pkg, tostring(loaded), tostring(visible)))
  end)
  local n = 0
  for _, wdg in ipairs(liveInstances("UserWidget")) do
    local inVp = false; pcall(function() inVp = wdg:IsInViewport() end)
    if inVp then n = n + 1; log("WIDGET[" .. tag .. "] " .. wdg:GetClass():GetFName():ToString()) end
  end
  log("WIDGETS[" .. tag .. "] in viewport: " .. n)
end
RegisterConsoleCommandHandler("sdmp_levels", function() logLevels("manual"); return true end)

-- ---------- client side: take control after joining ----------
-- Only the menu itself is removed. The loading screen is the game's own transition widget; removing it
-- mid-transition crashed a client. The game takes it down by itself.
-- The death/respawn screens are removed too: their buttons call the game's respawn, which resets the HOST
-- (hard-wired to player controller 0). The host respawns joined players itself.
local MENU_WIDGETS = { MenuWidget_C = true, MainMenu_C = true, RespawnScreen_C = true, BP_RespawnHUD_C = true, ScreenPermadeath_C = true, QuitWidgetRespawn_C = true }
local function clientTakeControl()
  local pc = UEHelpers.GetPlayerController()
  local ok, pawn = pcall(function() return pc.Pawn end)
  if not (ok and valid(pawn)) then state.pawnSince = nil; return end
  state.pawnSince = state.pawnSince or os.time()
  if os.time() - state.pawnSince < 4 then return end   -- let the travel settle first
  -- The game's single-player start flow also runs on a client when the world level streams in and spawns a
  -- local, non-networked player. Locally spawned actors have local role Authority (3); real ones are proxies.
  for _, p in ipairs(liveInstances("BP_PlayerCharacter_C")) do
    local okr, role = pcall(function() return p:GetLocalRole() end)
    if okr and tonumber(role) == 3 then
      log("client: destroying locally spawned phantom pawn " .. short(p))
      pcall(function() p:K2_DestroyActor() end)
    end
  end
  local removed = 0
  for _, wdg in ipairs(liveInstances("UserWidget")) do
    local cls = wdg:GetClass():GetFName():ToString()
    local inVp = false; pcall(function() inVp = wdg:IsInViewport() end)
    if MENU_WIDGETS[cls] and inVp then
      if pcall(function() wdg:RemoveFromParent() end) then removed = removed + 1; log("client: removed menu widget " .. cls) end
    end
  end
  if removed > 0 or not state.inputFixed then
    local okm, errm = pcall(function()
      StaticFindObject("/Script/UMG.Default__WidgetBlueprintLibrary"):SetInputMode_GameOnly(pc, false)
      pc.bShowMouseCursor = false
      log("client: input mode set to game-only")
    end)
    if not okm then log("client: input mode error: " .. tostring(errm)) end
    state.inputFixed = true
  end
end

-- The game's own Event_LoadLevel usually streams the world in and the menu level out on the client by itself.
-- Step in only if it hasn't, and never during the transition (unloading MainMenu while its level Blueprint
-- was running crashed a client).
local function ensureLevelLoaded()
  if not state.pawnSince or os.time() - state.pawnSince < 6 then return end
  eachStreamingLevel(function(ls, pkg, loaded, visible)
    if pkg:find(LEVEL_NAME, 1, true) and not (loaded and visible) then
      log("client: requesting stream-in of " .. pkg)
      pcall(function() ls:SetShouldBeLoaded(true); ls:SetShouldBeVisible(true) end)
    elseif pkg:find("MainMenu", 1, true) and (loaded or visible) then
      log("client: unloading " .. pkg)
      pcall(function() ls:SetShouldBeVisible(false); ls:SetShouldBeLoaded(false) end)
    end
  end)
end

-- ---------- net driver selection ----------
-- GameNetDriver is SteamSockets by default. Rewrite the definition so the next `open` uses plain IP.
-- (Only works when the game was NOT launched through Steam; see the launcher .bat.)
local DRIVER_STEAM = "/Script/SteamSockets.SteamSocketsNetDriver"
local DRIVER_IP = "/Script/OnlineSubsystemUtils.IpNetDriver"
local function setNetDriver(className)
  local targets = { StaticFindObject("/Script/Engine.Default__GameEngine") }
  pcall(function() targets[#targets+1] = UEHelpers.GetEngine() end)
  for _, ge in ipairs(targets) do
    if valid(ge) then
      local ok, err = pcall(function()
        ge.NetDriverDefinitions:ForEach(function(i, el)
          local d = el:get()
          if d.DefName:ToString() == "GameNetDriver" then
            d.DriverClassName = FName(className)
            log(string.format("setNetDriver: %s GameNetDriver -> %s", short(ge), d.DriverClassName:ToString()))
          end
        end)
      end)
      if not ok then log("setNetDriver failed on " .. short(ge) .. ": " .. tostring(err)) end
    end
  end
end
RegisterConsoleCommandHandler("sdmp_driver", function(full, params)
  local which = (params[1] or ""):lower()
  if which == "ip" then setNetDriver(DRIVER_IP) elseif which == "steam" then setNetDriver(DRIVER_STEAM) else log("usage: sdmp_driver ip|steam") end
  return true
end)

-- ---------- main menu buttons ----------
-- Two instances of the game's own ButtonWidget_C go under the Quit button of MenuWidget_C.
-- Clicks are detected by hooking ButtonWidget_C's click event and comparing the instance address.
local BTN_CLASS = "/Game/UI/Menus/ButtonWidget.ButtonWidget_C"
setButtonText = function(w, label)
  pcall(function() w.Text = FText(label) end)
  pcall(function() w.ButtonText:SetText(FText(label)) end)
end

local function findMenuWidget()
  for _, w in ipairs(liveInstances("UserWidget")) do
    if w:GetClass():GetFName():ToString() == "MenuWidget_C" then
      local inVp = false; pcall(function() inVp = w:IsInViewport() end)
      if inVp then return w end
    end
  end
  return nil
end

-- copy the look of the game's own menu entry (button style, text font/colour/alignment, slot padding) onto ours
local function describeTree(w, depth, out)
  depth = depth or 0; out = out or {}
  if not valid(w) or depth > 4 then return out end
  local line = string.rep("  ", depth) .. w:GetClass():GetFName():ToString() .. " " .. w:GetFName():ToString()
  pcall(function() local s = w.Slot; if valid(s) then line = line .. " [slot " .. s:GetClass():GetFName():ToString() .. "]" end end)
  out[#out+1] = line
  pcall(function()
    local n = w:GetChildrenCount()
    for i = 0, n - 1 do describeTree(w:GetChildAt(i), depth + 1, out) end
  end)
  return out
end

local function styleLikeMenu(w, menu, refButton, refText)
  local steps = {}
  local function try(name, f) local ok, err = pcall(f); steps[#steps+1] = name .. (ok and "" or ("!" .. tostring(err):sub(1, 50))) end
  -- button visuals: try a direct struct copy first, then the setter, then resync
  try("stylecopy", function() w.Button.WidgetStyle = refButton.WidgetStyle end)
  try("style", function() w.Button:SetStyle(refButton.WidgetStyle) end)
  -- text visuals
  try("font", function() w.ButtonText:SetFont(refText.Font) end)
  try("color", function() w.ButtonText:SetColorAndOpacity(refText.ColorAndOpacity) end)
  try("just", function() w.ButtonText:SetJustification(refText.Justification) end)
  try("shadow", function() w.ButtonText:SetShadowOffset(refText.ShadowOffset); w.ButtonText:SetShadowColorAndOpacity(refText.ShadowColorAndOpacity) end)
  -- text placement inside the button: copy the reference text's slot alignment + padding
  try("textslot", function()
    local rs, ms = refText.Slot, w.ButtonText.Slot
    ms:SetPadding(rs.Padding)
    ms:SetHorizontalAlignment(rs.HorizontalAlignment)
    ms:SetVerticalAlignment(rs.VerticalAlignment)
  end)
  -- our widget's slot in the vertical box: copy the reference button's slot padding / size / alignment
  try("boxslot", function()
    local rs, ms = refButton.Slot, w.Slot
    ms:SetPadding(rs.Padding)
    ms:SetHorizontalAlignment(rs.HorizontalAlignment)
    ms:SetVerticalAlignment(rs.VerticalAlignment)
    ms:SetSize(rs.Size)
  end)
  -- ButtonWidget_C may size its text from its own variable; mirror the reference font size
  try("textsize", function() w.TextSize = refText.Font.Size end)
  local failed = {}
  for _, s in ipairs(steps) do if s:find("!", 1, true) then failed[#failed+1] = s end end
  if #failed > 0 then log("menu: style steps failed: " .. table.concat(failed, " ")) end
end

local function makeMenuButton(menu, label, refButton, index)
  local cls = StaticFindObject(BTN_CLASS)
  if not valid(cls) then error("ButtonWidget_C class not loaded") end
  local wbl = StaticFindObject("/Script/UMG.Default__WidgetBlueprintLibrary")
  local w = wbl:Create(UEHelpers.GetWorld(), cls, UEHelpers.GetPlayerController())
  if not valid(w) then error("Create() returned nothing") end
  local parent = refButton:GetParent()
  local pname = valid(parent) and parent:GetClass():GetFName():ToString() or "?"
  if pname == "VerticalBox" then
    parent:AddChildToVerticalBox(w)
  elseif pname == "CanvasPanel" then
    local refSlot = refButton.Slot
    local pos, size = refSlot:GetPosition(), refSlot:GetSize()
    local slot = parent:AddChildToCanvas(w)
    slot:SetAutoSize(false)
    slot:SetPosition({ X = pos.X, Y = pos.Y + (size.Y + 6) * index })
    slot:SetSize({ X = size.X, Y = size.Y })
  else
    w:AddToViewport(50)
  end
  setButtonText(w, label)
  log("menu: added '" .. label .. "' (parent " .. pname .. ")")
  pcall(function() styleLikeMenu(w, menu, refButton, menu.QuitText) end)
  return w
end

local function injectMenuButtons()
  local menu = findMenuWidget()
  if not menu then return end
  if netDriver() then
    if isClient() then return end
    if menuUI.statusMenu and valid(menuUI.statusMenu) and menuUI.statusMenu:GetAddress() == menu:GetAddress() and valid(menuUI.status) then return end
    menuUI.status = makeMenuButton(menu, "MP: HOSTING OK - now click New or Load", menu.Quit, 1)
    menuUI.statusMenu = menu
    return
  end
  if menuUI.menu and valid(menuUI.menu) and menuUI.menu:GetAddress() == menu:GetAddress() and valid(menuUI.host) and valid(menuUI.join) then return end
  local ref = menu.Quit
  if not valid(ref) then error("Quit button not found on menu") end
  menuUI.host = makeMenuButton(menu, "MP: HOST", ref, 1)
  menuUI.join = makeMenuButton(menu, "MP: JOIN " .. (readConfig().host_ip or "?"), ref, 2)
  menuUI.menu = menu
  -- The game's list has separator widgets between entries (the thin bars). Clone the one before Quit and
  -- put copies before each of our entries so the rhythm matches.
  pcall(function()
    local box = ref:GetParent()
    local n = box:GetChildrenCount()
    local qi = -1
    for i = 0, n - 1 do
      if box:GetChildAt(i):GetAddress() == ref:GetAddress() then qi = i end
    end
    if qi < 1 then return end
    local sep = box:GetChildAt(qi - 1)
    local sepClass = sep:GetClass()
    local sepName = sepClass:GetFName():ToString()
    if sepName == "Button" then return end  -- no separator widgets; entries are adjacent buttons
    local function cloneSep()
      local w = StaticConstructObject(sepClass, menu.WidgetTree)
      if not valid(w) then w = StaticConstructObject(sepClass, box) end
      if not valid(w) then error("StaticConstructObject(" .. sepName .. ") failed") end
      pcall(function() w:SetBrush(sep.Brush) end)            -- Image / Border
      pcall(function() w:SetSize(sep.Size) end)              -- Spacer
      pcall(function() w:SetVisibility(sep.Visibility) end)
      return w
    end
    local okc, errc = pcall(function()
      local s1, s2 = cloneSep(), cloneSep()
      -- order after Quit: sep, HOST, sep, JOIN  (InsertChildAt isn't exposed; our two are last, so re-add in order)
      box:RemoveChild(menuUI.host); box:RemoveChild(menuUI.join)
      box:AddChildToVerticalBox(s1); box:AddChildToVerticalBox(menuUI.host); box:AddChildToVerticalBox(s2); box:AddChildToVerticalBox(menuUI.join)
      pcall(function() styleLikeMenu(menuUI.host, menu, ref, menu.QuitText); styleLikeMenu(menuUI.join, menu, ref, menu.QuitText) end)
      for _, pair in ipairs({ { s1, sep }, { s2, sep } }) do
        pcall(function() local ms, rs = pair[1].Slot, pair[2].Slot; ms:SetPadding(rs.Padding); ms:SetSize(rs.Size); ms:SetHorizontalAlignment(rs.HorizontalAlignment); ms:SetVerticalAlignment(rs.VerticalAlignment) end)
      end
      local sz = "?"; pcall(function() sz = string.format("%.0fx%.0f", sep.Size.X, sep.Size.Y) end)
      log("menu: inserted two " .. sepName .. " separators (size " .. sz .. ") cloned from child " .. (qi - 1))
    end)
    if not okc then log("menu: separator insert failed: " .. tostring(errc)) end
  end)
end

local function onMenuButtonClicked(w)
  if not valid(w) then return end
  local a = w:GetAddress()
  if valid(menuUI.host) and a == menuUI.host:GetAddress() then
    log("menu: HOST clicked"); setButtonText(menuUI.host, "MP: HOSTING...")
    state.useIpDriver = true; setNetDriver(DRIVER_IP); cmdHost()
  elseif valid(menuUI.join) and a == menuUI.join:GetAddress() then
    local cfg = readConfig()
    if cfg.host_ip then log("menu: JOIN clicked"); setButtonText(menuUI.join, "MP: JOINING..."); setNetDriver(DRIVER_IP); cmdJoin(cfg.host_ip, true)
    else setButtonText(menuUI.join, "MP: no host_ip in sdmp.ini") end
  end
end

-- ---------- commands ----------
cmdHost = function()
  local nd = netDriver()
  if nd and not isClient() then
    log("sdmp_host: already hosting (press F6 for status)")
    status("host")
    return true
  end
  log("sdmp_host: issuing open PersistentLevel?listen")
  consoleCmd("open PersistentLevel?listen")
  state.hosting = true
  state.hostAttempts = (state.hostAttempts or 0) + 1
  after(8, function()
    status("host")
    local nd2 = netDriver()
    if nd2 and not isClient() then
      log("HOSTING OK: listen server is up (" .. nd2:GetClass():GetFName():ToString() .. "). Now click New Game / Continue.")
      if valid(menuUI.host) then setButtonText(menuUI.host, "MP: HOSTING OK - now click New or Load") end
      state.hostAttempts = 0
    elseif state.hostAttempts < 4 then
      log("listen did not come up, retrying in 5s (attempt " .. (state.hostAttempts + 1) .. "/4)")
      after(5, function() if state.useIpDriver then setNetDriver(DRIVER_IP) end; cmdHost() end, "host-retry")
    else
      log("HOSTING FAILED after 4 attempts. Restart the game, wait on the main menu 60s, try again.")
      state.hostAttempts = 0
    end
  end, "host-check")
  return true
end

-- did the host answer? LastReceiveTime is stamped at creation; it only moves when a packet arrives.
local seenRecv = {}
local function hostReplied()
  if isClient() then return true end
  for _, c in ipairs(liveInstances("NetConnection")) do
    local ok, t = pcall(function() return c.LastReceiveTime end)
    if ok and tonumber(t) then
      local key = c:GetAddress()
      if seenRecv[key] == nil then seenRecv[key] = tonumber(t)
      elseif tonumber(t) > seenRecv[key] + 0.001 then return true end
    end
  end
  return false
end

local joinTask
local function joinProgress(url)
  local started = os.time()
  local found = false
  seenRecv = {}
  cancel(joinTask)
  joinTask = every(1, function()
    local elapsed = os.time() - started
    if isClient() then
      local ok, pawn = pcall(function() return UEHelpers.GetPlayerController().Pawn end)
      if ok and valid(pawn) then log("JOIN: connected and in the world"); cancel(joinTask); return end
      if not found then found = true; log("JOIN: host found, loading world...") end
      if valid(menuUI.join) then setButtonText(menuUI.join, "MP: HOST FOUND, LOADING...") end
      return
    end
    if hostReplied() then
      if not found then found = true; log("JOIN: host found (" .. url .. "), loading...") end
      if valid(menuUI.join) then setButtonText(menuUI.join, "MP: HOST FOUND, LOADING...") end
      if elapsed > 90 then log("JOIN: stuck after host reply for 90s, giving up"); state.joining = false; cancel(joinTask) end
      return
    end
    if elapsed >= 15 then
      log("JOIN: HOST NOT FOUND after 15s (" .. url .. "). Is the host past HOSTING OK? Is Radmin green?")
      if valid(menuUI.join) then setButtonText(menuUI.join, "MP: HOST NOT FOUND - click to retry") end
      state.joining = false; cancel(joinTask); return
    end
    if valid(menuUI.join) then setButtonText(menuUI.join, "MP: CONNECTING... " .. elapsed .. "s") end
  end, "join-progress")
end

cmdJoin = function(target, viaIp)
  if not target or target == "" then log("usage: sdmp_join <SteamID64>   or   sdmp_join_ip <ip[:port]>"); return true end
  local url = viaIp and target or ("steam." .. target)
  log("sdmp_join: open " .. url)
  state.joining = true; state.target = url
  consoleCmd("open " .. url)
  joinProgress(url)
  after(5, function() status("join+5s") end, "join-status")
  after(40, function() status("join+40s") end, "join-status")
  return true
end

RegisterConsoleCommandHandler("sdmp_host", function() state.useIpDriver = true; setNetDriver(DRIVER_IP); return cmdHost() end)
RegisterConsoleCommandHandler("sdmp_host_steam", function() state.useIpDriver = false; setNetDriver(DRIVER_STEAM); return cmdHost() end)
RegisterConsoleCommandHandler("sdmp_join", function(full, params) return cmdJoin(params[1], false) end)
RegisterConsoleCommandHandler("sdmp_join_ip", function(full, params) setNetDriver(DRIVER_IP); return cmdJoin(params[1], true) end)
RegisterConsoleCommandHandler("sdmp_status", function() status("manual"); return true end)
RegisterConsoleCommandHandler("sdmp_spawn", function() state.spawned = {}; spawnMissing(); return true end)
RegisterKeyBind(Key.F7, {}, function() log("F7: host with IP driver"); state.useIpDriver = true; setNetDriver(DRIVER_IP); cmdHost() end)
RegisterKeyBind(Key.F7, {ModifierKey.CONTROL}, function() log("Ctrl+F7: host with Steam Sockets driver"); state.useIpDriver = false; setNetDriver(DRIVER_STEAM); cmdHost() end)
RegisterKeyBind(Key.F6, {}, function() status("F6") end)
-- F5: copy this PC's SDMP.log to the Desktop so a joiner can hand it to the host
RegisterKeyBind(Key.F5, {}, function()
  status("F5")
  local ok, err = pcall(function()
    local src = io.open("SDMP.log", "rb"); local data = src:read("*a"); src:close()
    local desktop = (os.getenv("USERPROFILE") or ".") .. "\\Desktop\\SDMP-log.txt"
    local dst = io.open(desktop, "wb"); dst:write(data); dst:close()
    log("F5: log copied to " .. desktop .. " - send that file to the host")
  end)
  if not ok then log("F5: copy failed: " .. tostring(err)) end
end)
RegisterKeyBind(Key.F8, {}, function()
  local cfg = readConfig()
  if cfg.host_steamid then log("F8: joining host_steamid from sdmp.ini"); cmdJoin(cfg.host_steamid, false)
  else log("F8: no host_steamid in sdmp.ini") end
end)
RegisterKeyBind(Key.F9, {}, function()
  local cfg = readConfig()
  if cfg.host_ip then log("F9: joining host_ip from sdmp.ini (IP driver)"); setNetDriver(DRIVER_IP); cmdJoin(cfg.host_ip, true)
  else log("F9: no host_ip in sdmp.ini") end
end)

-- ---------- hooks (native engine functions exist at load time) ----------
pcall(function()
  RegisterHook("/Script/Engine.GameModeBase:K2_PostLogin", function(ctx, newPlayer)
    local who = "?"; pcall(function() who = short(newPlayer:get()) end)
    log("PLAYER JOINED: " .. who)
    after(3, spawnMissing, "spawn-after-login")
    after(8, rebroadcastAppearance, "appearance-after-login")
    after(20, rebroadcastAppearance, "appearance-after-login-2")
  end)
end)
pcall(function()
  RegisterHook("/Script/Engine.GameModeBase:K2_OnLogout", function(ctx, exiting)
    local who = "?"; pcall(function() who = short(exiting:get()) end)
    log("PLAYER LEFT: " .. who); state.spawned[who] = nil
  end)
end)
for _, fn in ipairs({
  "/Script/Engine.PlayerController:ClientReturnToMainMenuWithTextReason",
  "/Script/Engine.PlayerController:ClientRestart",
  "/Script/Engine.PlayerController:UnPossess",
}) do
  pcall(function()
    RegisterHook(fn, function(ctx, ...)
      local parts = {}
      for _, a in ipairs({...}) do pcall(function() local v = a:get(); local ok, s = pcall(function() return v:ToString() end); parts[#parts+1] = ok and s or tostring(v) end) end
      log("NET-EVENT " .. fn:gsub("^.*:", "") .. " [" .. table.concat(parts, ", ") .. "]")
    end)
  end)
end

-- Blueprint classes are not loaded when this script starts: register those hooks later, from the scheduler.
after(12, function()
  local ok, err = pcall(function()
    RegisterHook(BTN_CLASS .. ":BndEvt__ButtonWidget_Button_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature", function(ctx)
      local w; pcall(function() w = ctx:get() end)
      onMenuButtonClicked(w)
    end)
  end)
  log(ok and "menu: click hook installed" or ("menu: click hook failed: " .. tostring(err):sub(1, 100)))
  -- death of a joined player's body: the multicast runs on the server too; remember the pawn so spawnMissing respawns it
  pcall(function()
    RegisterHook("/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C:MC_PlayerDead", function(ctx)
      local p; pcall(function() p = ctx:get() end)
      if not valid(p) or isClient() then return end
      local hp; pcall(function() hp = UEHelpers.GetPlayerController().Pawn end)
      if valid(hp) and hp:GetAddress() == p:GetAddress() then log("host died") return end
      state.deadPawns = state.deadPawns or {}
      state.deadPawns[p:GetAddress()] = os.time()
      log("joined player's body died: " .. short(p) .. " (respawn in ~6s)")
      -- the game's death logic is written for one player and acts on "player 0" = the host: it kills the host's
      -- input (no death screen, just frozen). Give the host its controls back shortly after.
      for _, d in ipairs({ 1, 4, 8 }) do after(d, restoreHostControl, "restore-host-control") end
    end)
  end)
  -- clothing: record the host's attach calls (server) / count received ones (client)
  pcall(function()
    RegisterHook("/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C:MC_AttachClothing", function(ctx, clothing, mesh, parts, male, bodyPart, updateAll)
      if isClient() then
        local bp = "?"; pcall(function() bp = bodyPart:get():ToString() end)
        state.clothingReceived = (state.clothingReceived or 0) + 1
        log("appearance: received clothing for " .. bp)
      else
        recordClothingCall(ctx, clothing, mesh, parts, male, bodyPart, updateAll)
      end
    end)
  end)
  -- server->client movement corrections: count them (rubber-banding indicator, shown by F6)
  pcall(function()
    RegisterHook("/Script/Engine.Character:ClientAdjustPosition", function(ctx) state.adjusts = (state.adjusts or 0) + 1 end)
  end)
  for _, fn in ipairs({
    "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Event_LoadLevel",
    "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Survival_SpawnPlayer",
    "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Survival_Respawn",
    "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C:ReceivePossess",
    "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C:Svr_RequestRespawn_Random",
    "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C:Svr_RequestRespawnSuicide",
    "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C:Client_Died",
    "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C:Death_PlayerStats",
    "/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C:MC_PlayerDead",
  }) do
    local ok2, err2 = pcall(function()
      RegisterHook(fn, function(ctx, ...)
        local who = ""; pcall(function() who = short(ctx:get()) end)
        log("GAME-FLOW " .. fn:gsub("^.*:", "") .. " self=" .. who .. (isClient() and " (CLIENT)" or ""))
      end)
    end)
    if not ok2 then log("hook failed: " .. fn .. " : " .. tostring(err2):sub(1, 80)) end
  end
end, "late-hooks")

-- ---------- network smoothing for other players' bodies (both sides) ----------
-- A remote player's pawn is a simulated proxy here; without exponential smoothing it snaps to each net update.
local smoothed = {}
local firstSeen = {}
local hostPcCache
local function ensureSmoothing()
  local myPawn; pcall(function() hostPcCache = UEHelpers.GetPlayerController(); myPawn = hostPcCache.Pawn end)
  for _, p in ipairs(liveInstances("BP_PlayerCharacter_C")) do
    local key = p:GetAddress()
    local mine = valid(myPawn) and myPawn:GetAddress() == key
    firstSeen[key] = firstSeen[key] or os.time()
    -- server: joined players own their movement (no position corrections = no rubber-banding on their screen),
    -- but only once they have had ~20s to stream the world in, and only while they are standing on something
    if not mine and not isClient() and os.time() - firstSeen[key] >= 20 and not smoothed[key .. "auth"] then
      pcall(function()
        local v = p:GetVelocity()
        local ctrl = p.Controller
        local remote = valid(ctrl) and valid(hostPcCache) and ctrl:GetAddress() ~= hostPcCache:GetAddress()
        if remote and math.abs(v.Z) < 50 then
          local cm = p.CharacterMovement
          cm.bServerAcceptClientAuthoritativePosition = true
          cm.bIgnoreClientMovementErrorChecksAndCorrection = true
          smoothed[key .. "auth"] = true
          log("movement: " .. p:GetFName():ToString() .. " is now client-authoritative")
        end
      end)
    end
    if not smoothed[key] and not mine then
      smoothed[key] = true
      pcall(function()
        local cm = p.CharacterMovement
        local before = string.format("smoothing=%s locTime=%.3f rotTime=%.3f lsLoc=%.3f netUpd=%.0f minUpd=%.0f repMove=%s role=%s", tostring(cm.NetworkSmoothingMode), cm.NetworkSimulatedSmoothLocationTime, cm.NetworkSimulatedSmoothRotationTime, cm.ListenServerNetworkSimulatedSmoothLocationTime, p.NetUpdateFrequency, p.MinNetUpdateFrequency, tostring(p.bReplicateMovement), tostring(p:GetLocalRole()))
        -- ENetworkSmoothingMode: 0 Disabled, 1 Linear, 2 Exponential. The game already uses Exponential (2).
        if tostring(cm.NetworkSmoothingMode) == "0" then cm.NetworkSmoothingMode = 2 end
        if p.NetUpdateFrequency < 60 then p.NetUpdateFrequency = 100 end
        if p.MinNetUpdateFrequency < 20 then p.MinNetUpdateFrequency = 30 end
        -- the listen server smooths other players over only 0.04s by default; over a VPN that reads as stutter
        if cm.ListenServerNetworkSimulatedSmoothLocationTime < 0.1 then cm.ListenServerNetworkSimulatedSmoothLocationTime = 0.12 end
        if cm.ListenServerNetworkSimulatedSmoothRotationTime < 0.05 then cm.ListenServerNetworkSimulatedSmoothRotationTime = 0.08 end
        if cm.NetworkSimulatedSmoothLocationTime < 0.12 then cm.NetworkSimulatedSmoothLocationTime = 0.12 end
        log("smoothing: " .. p:GetFName():ToString() .. " " .. before .. " -> mode=" .. tostring(cm.NetworkSmoothingMode) .. " minUpd=" .. tostring(p.MinNetUpdateFrequency))
      end)
    end
  end
end

-- ---------- host control recovery ----------
-- Undo everything the single-player death flow may have done to the host's controller when SOMEONE ELSE died.
restoreHostControl = function()
  if isClient() then return end
  local pc = UEHelpers.GetPlayerController()
  local hp; pcall(function() hp = pc.Pawn end)
  local done = {}
  local function try(name, f) if pcall(f) then done[#done+1] = name end end
  try("ignoreflags", function() pc:ResetIgnoreInputFlags() end)
  try("pc-input", function() pc:EnableInput(pc) end)
  if valid(hp) then
    try("pawn-input", function() hp:EnableInput(hp) end)
    try("pawn-input-pc", function() hp:EnableInput(pc) end)
    try("viewtarget", function() pc:SetViewTargetWithBlend(hp, 0.0, 0, 0.0, false) end)
  end
  try("inputmode", function() StaticFindObject("/Script/UMG.Default__WidgetBlueprintLibrary"):SetInputMode_GameOnly(pc, false); pc.bShowMouseCursor = false end)
  try("timedilation", function() UEHelpers.GetGameplayStatics():SetGlobalTimeDilation(UEHelpers.GetWorld(), 1.0) end)
  try("unpause", function() UEHelpers.GetGameplayStatics():SetGamePaused(UEHelpers.GetWorld(), false) end)
  log("host control restored: " .. table.concat(done, " "))
end
RegisterKeyBind(Key.F4, {}, function() log("F4: restore host control"); pcall(restoreHostControl) end)

-- ---------- late joiners: equipment and clothing ----------
-- Weapons/items attached to a player are pickup actors that do not replicate (bReplicates=false), so joiners never
-- see them. Turn replication on for anything attached to a player body; attachment then replicates too.
local repFixed = {}
local function replicateAttachedItems()
  if isClient() then return end
  local n = 0
  for _, a in ipairs(liveInstances("Actor")) do
    local key = a:GetAddress()
    if not repFixed[key] then
      local ok, parent = pcall(function() return a:GetAttachParentActor() end)
      if ok and valid(parent) and parent:GetClass():GetFName():ToString() == "BP_PlayerCharacter_C" then
        repFixed[key] = true
        local isRep = false; pcall(function() isRep = a:GetIsReplicated() end)
        if not isRep then
          pcall(function() a:SetReplicates(true) end)
          n = n + 1
          log("replicate: " .. a:GetClass():GetFName():ToString() .. " attached to a player -> replicated")
        end
      end
    end
  end
end

-- Clothing is applied through the MC_AttachClothing multicast at equip time; late joiners missed those calls.
-- We record every call the host's body makes (arguments included) and replay them when someone joins.
local PARTS_FIELDS = {
  "MaleTorsoMesh_37_C39419A54F846168C8ACC7B8047249B8", "MaleArmsMesh_38_E3992D3D4D3FC15857DCCA96943DF404",
  "MaleBicepsMesh_58_A5C488CE417D90B275C89D85A579F848", "MaleHandsMesh_39_62A6D44C46074AB07761FD8486836B1E",
  "MaleLegsMesh_40_D743A1EA4C0458D9DB7686B580B34B55", "MaleLowerThighsMesh_60_1BB76DBD438060796E0670BACC379CFB",
  "MaleLowerLegsMesh_41_C71508734756C346F2E4E5B00E2D7D7A", "MaleFeetMesh_42_052101B64D2CB0C9572A4AAD3997D93B",
  "FemaleTorsoMesh_49_66B3BA484F8278F2133583B2677358EA", "FemaleArmsMesh_50_5D08A0FA4B92C459DDDD8E8043029F2F",
  "FemaleBicepsMesh_63_742947C24722CA2991518EA18DF1C2EC", "FemaleHandsMesh_51_994CCC674C6D50AFD49448941EA98F9F",
  "FemaleLegsMesh_52_7AE6631D44A06557F6DCB28A267ABCF0", "FemaleLowerThighsMesh_64_6FC37310431BCF7E935A9A80E8A8CEFD",
  "FemaleLowerLegsMesh_53_0981B7444A0C7933ABE436BAE54E9BC8", "FemaleFeetMesh_54_759E5B484609B6B259ECB5ACB9BFA58A",
}
local clothingCalls = {}   -- bodyPart -> { clothing, mesh, parts(table), male, bodyPart, updateAll }
local function recordClothingCall(ctx, clothing, mesh, parts, male, bodyPart, updateAll)
  if isClient() then return end
  local hp; pcall(function() hp = UEHelpers.GetPlayerController().Pawn end)
  local self; pcall(function() self = ctx:get() end)
  if not (valid(hp) and valid(self) and self:GetAddress() == hp:GetAddress()) then return end
  local call = {}
  pcall(function() call.clothing = clothing:get() end)
  pcall(function() call.mesh = mesh:get() end)
  pcall(function() call.male = male:get() end)
  pcall(function() call.bodyPart = bodyPart:get():ToString() end)
  pcall(function() call.updateAll = updateAll:get() end)
  call.parts = {}
  pcall(function()
    local s = parts:get()
    for _, f in ipairs(PARTS_FIELDS) do pcall(function() local v = s[f]; if valid(v) then call.parts[f] = v end end) end
  end)
  if call.bodyPart then
    clothingCalls[call.bodyPart] = call
    log("appearance: recorded clothing call for " .. call.bodyPart .. " (mesh " .. (valid(call.mesh) and call.mesh:GetFName():ToString() or "none") .. ")")
  end
end

local function rebroadcastAppearance()
  if isClient() then return end
  local hp; pcall(function() hp = UEHelpers.GetPlayerController().Pawn end)
  if not valid(hp) then return end
  local n = 0
  for part, c in pairs(clothingCalls) do
    local ok, err = pcall(function() hp:MC_AttachClothing(c.clothing, c.mesh, c.parts, c.male, FName(c.bodyPart), c.updateAll) end)
    if ok then n = n + 1 else log("appearance: re-send failed for " .. part .. ": " .. tostring(err)) end
  end
  log("appearance: re-sent " .. n .. " clothing call(s) to clients")
  repFixed = {}  -- re-scan attachments too
  pcall(replicateAttachedItems)
end

-- ---------- periodic work ----------
every(5, function() if netDriver() then pcall(ensureSmoothing) end end, "smoothing")
every(10, function() if state.hosting then pcall(replicateAttachedItems) end end, "replicate-items")
every(2, function()
  local ok, err = pcall(injectMenuButtons)
  if not ok and not menuUI.loggedErr then menuUI.loggedErr = true; log("menu: inject error: " .. tostring(err)) end
end, "menu")
every(5, function()
  if state.hosting then pcall(spawnMissing) end
  if state.joining and isClient() then pcall(ensureLevelLoaded); pcall(clientTakeControl) end
end, "main")

-- ---------- dev helpers ----------
local function spawnTest()
  local world = UEHelpers.GetWorld()
  local cls = StaticFindObject(PLAYER_CLASS)
  local hp = UEHelpers.GetPlayerController().Pawn
  if not valid(hp) then log("spawntest: no host pawn yet"); return false end
  local l = hp:K2_GetActorLocation()
  local ok, pawn = pcall(function() return world:SpawnActor(cls, { X = l.X + 250, Y = l.Y, Z = l.Z + 50 }, { Pitch = 0, Yaw = 0, Roll = 0 }) end)
  log(string.format("spawntest: ok=%s result=%s", tostring(ok), ok and short(pawn) or tostring(pawn)))
  return true
end
RegisterConsoleCommandHandler("sdmp_spawntest", function() spawnTest(); return true end)

-- env SDMP_DEV=hostip -> auto-host at 35s, enter the world at 50s;  SDMP_DEV=joinip:<ip> -> auto-join at 45s
do local role = os.getenv("SDMP_DEV")
  if role and role ~= "" then
    logf = io.open("SDMP_" .. role:gsub("[^%w]", "_") .. ".log", "a")
    log("SDMP_DEV=" .. role)
    if role == "host" or role == "hostip" then
      after(35, function() if role == "hostip" then state.useIpDriver = true; setNetDriver(DRIVER_IP) end; cmdHost() end, "dev-host")
      after(50, function()
        local ok, err = pcall(function() UEHelpers.GetGameInstance():Event_LoadLevel(FName(LEVEL_NAME)) end)
        log("dev host: Event_LoadLevel(" .. LEVEL_NAME .. ") ok=" .. tostring(ok) .. " " .. tostring(err))
      end, "dev-enter")
      -- the dev entry path spawns the host at the origin (falling forever); move it to a known good spot once
      local tp; tp = every(2, function()
        local ok, hp = pcall(function() return UEHelpers.GetPlayerController().Pawn end)
        if ok and valid(hp) then
          pcall(function() hp:K2_SetActorLocation({ X = 165450, Y = 49719, Z = 1600 }, false, {}, true) end)
          log("dev host: teleported host pawn to the known spawn area"); cancel(tp)
        end
      end, "dev-teleport")
      every(15, function() status("dev-host") end, "dev-status")
      -- dev: count the game's own server RPCs on player pawns and sample the joined pawn's position (jitter hunt)
      local rpcCounts = {}
      after(14, function()
        for _, fn in ipairs({ "Svr_SetActorLocation", "Svr_SetActorRotation", "Svr_UpdateSpeed", "Svr_UpdateWalkSpeed", "Svr_UpdateSprintSpeed", "Svr_SetMovement", "Svr_Montage", "MC_UpdateSpeed", "Svr_UpdateCombatState", "Svr_Crouch", "Svr_UnCrouch" }) do
          pcall(function()
            RegisterHook("/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C:" .. fn, function(ctx, ...)
              local args = { ... }
              local who = "?"; pcall(function() who = ctx:get():GetFName():ToString() end)
              local k = fn .. "@" .. who; rpcCounts[k] = (rpcCounts[k] or 0) + 1
              if fn == "Svr_SetActorLocation" and (rpcCounts[k] % 20 == 1) then pcall(function() local v = args[1]:get(); log(string.format("dev host: Svr_SetActorLocation %s -> %.0f %.0f %.0f", who, v.X, v.Y, v.Z)) end) end
            end)
          end)
        end
      end, "dev-rpc-hooks")
      every(5, function()
        local parts = {}
        for k, v in pairs(rpcCounts) do parts[#parts+1] = k .. "=" .. v end
        table.sort(parts)
        if #parts > 0 then log("dev host: rpc counts " .. table.concat(parts, " ")) end
        rpcCounts = {}
        local hostPc = UEHelpers.GetPlayerController()
        for _, pc in ipairs(liveInstances("BP_PlayerController_C")) do
          if pc:GetAddress() ~= hostPc:GetAddress() then
            pcall(function() local p = pc.Pawn; local l = p:K2_GetActorLocation(); local v = p:GetVelocity(); log(string.format("dev host: joined pawn at %.0f %.0f %.0f vel %.0f %.0f %.0f", l.X, l.Y, l.Z, v.X, v.Y, v.Z)) end)
          end
        end
      end, "dev-rpc-report")
      -- dev: 110s in, mark the first joined player's pawn dead on the server to exercise our respawn
      if os.getenv("SDMP_DEVKILL") == "1" then
        after(80, function()
          local hostPc = UEHelpers.GetPlayerController()
          for _, pc in ipairs(liveInstances("BP_PlayerController_C")) do
            if pc:GetAddress() ~= hostPc:GetAddress() then
              local ok, err = pcall(function() pc.Pawn:MC_PlayerDead() end)
              log("dev host: called MC_PlayerDead on joined pawn ok=" .. tostring(ok) .. " " .. tostring(err))
            end
          end
        end, "dev-kill")
      end
    elseif role:sub(1, 5) == "join:" then
      after(45, function() cmdJoin(role:sub(6), true) end, "dev-join")
      every(15, function() status("dev-join") end, "dev-status")
    elseif role:sub(1, 7) == "joinip:" then
      after(45, function() setNetDriver(DRIVER_IP); cmdJoin(role:sub(8), true) end, "dev-join")
      every(15, function() status("dev-join") end, "dev-status")
      every(5, function()
        local ok, pawn = pcall(function() return UEHelpers.GetPlayerController().Pawn end)
        if ok and valid(pawn) then
          local l, v = pawn:K2_GetActorLocation(), pawn:GetVelocity()
          log(string.format("dev client: pawn=%s at %.0f %.0f %.0f vel %.0f %.0f %.0f", pawn:GetFName():ToString(), l.X, l.Y, l.Z, v.X, v.Y, v.Z))
        else log("dev client: no pawn") end
      end, "dev-pawnwatch")
    end
  end
end

-- <Win64>/SDMP_autohost.txt ("ip 25" = IP driver, host after 25s): host automatically, spawntest once in the world
do local f = io.open("SDMP_autohost.txt", "r"); if f then
  local mode = (f:read("*l") or ""):gsub("%s", ""); f:close()
  local delay = tonumber(mode:match("(%d+)")) or 35
  local useIp = mode:find("ip") ~= nil
  log("SDMP_autohost.txt present: hosting in " .. delay .. "s (ip=" .. tostring(useIp) .. ")")
  after(delay, function() if useIp then state.useIpDriver = true; setNetDriver(DRIVER_IP) end; cmdHost() end, "autohost")
  local t; t = every(5, function()
    local ok, hp = pcall(function() return UEHelpers.GetPlayerController().Pawn end)
    if ok and valid(hp) then status("in-world"); spawnTest(); cancel(t) end
  end, "autohost-spawntest")
end end

do local cfg = readConfig(); log("sdmp.ini: host_steamid=" .. tostring(cfg.host_steamid) .. " host_ip=" .. tostring(cfg.host_ip)) end
log("SDMP v" .. VERSION .. " loaded. Menu: MP: HOST / MP: JOIN. Keys: F7 host, F9 join, F6 status.")
