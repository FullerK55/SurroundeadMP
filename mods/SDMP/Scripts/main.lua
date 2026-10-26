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
local VERSION = "0.1.7"
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
local setButtonText, cmdHost, cmdJoin   -- defined later

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
  log(s)
  return s
end

-- ---------- host side: spawn pawns for joined players ----------
local function spawnFor(pc)
  local world = UEHelpers.GetWorld()
  local cls = StaticFindObject(PLAYER_CLASS)
  if not valid(cls) then log("spawnFor: player class not found"); return false end
  local loc = { X = 0, Y = 0, Z = 300 }
  pcall(function()
    local hp = UEHelpers.GetPlayerController().Pawn
    if valid(hp) then local l = hp:K2_GetActorLocation(); loc = { X = l.X + 250, Y = l.Y + 250, Z = l.Z + 100 } end
  end)
  local ok, pawn = pcall(function() return world:SpawnActor(cls, loc, { Pitch = 0, Yaw = 0, Roll = 0 }) end)
  if not ok or not valid(pawn) then log("spawnFor: SpawnActor failed: " .. tostring(pawn)); return false end
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
  if not (okh and valid(hostPawn)) then return end  -- host not in world yet
  for _, pc in ipairs(liveInstances("BP_PlayerController_C")) do
    if pc:GetAddress() ~= hostPc:GetAddress() then
      local okp, pawn = pcall(function() return pc.Pawn end)
      if not (okp and valid(pawn)) then
        local key = pc:GetFullName()
        if not state.spawned[key] then
          log("joined player without pawn: " .. key)
          if spawnFor(pc) then state.spawned[key] = true end
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
local MENU_WIDGETS = { MenuWidget_C = true, MainMenu_C = true }
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
  for _, fn in ipairs({
    "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Event_LoadLevel",
    "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Survival_SpawnPlayer",
    "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C:ReceivePossess",
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

-- ---------- periodic work ----------
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
      every(15, function() status("dev-host") end, "dev-status")
    elseif role:sub(1, 5) == "join:" then
      after(45, function() cmdJoin(role:sub(6), true) end, "dev-join")
      every(15, function() status("dev-join") end, "dev-status")
    elseif role:sub(1, 7) == "joinip:" then
      after(45, function() setNetDriver(DRIVER_IP); cmdJoin(role:sub(8), true) end, "dev-join")
      every(15, function() status("dev-join") end, "dev-status")
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
