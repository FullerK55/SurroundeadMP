-- SDMP: SurrounDead fan multiplayer mod (UE4SS Lua)
-- Console commands (open console with ~ or F10):
--   sdmp_host                 start a listen server (do this at the main menu, then click New Game / Continue)
--   sdmp_join <SteamID64>     join a host over Steam Sockets (do this at the main menu)
--   sdmp_join_ip <ip[:port]>  join over plain IP (fallback; host must use IP driver too)
--   sdmp_status               print world / net driver / pawn / connections
--   sdmp_spawn                (host) force-spawn pawns for any connected player without one
-- Keys: F7 = sdmp_host, F6 = sdmp_status
-- Log: <Win64>/SDMP.log

local UEHelpers = require("UEHelpers")
local VERSION = "0.1.4"
local LEVEL_NAME = "LongdownValley"
local PLAYER_CLASS = "/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C"

local logf = io.open("SDMP.log", "a")
local function log(s)
  local line = os.date("%Y-%m-%d %H:%M:%S ") .. s
  print("[SDMP] " .. s .. "\n")
  if logf then logf:write(line, "\n"); logf:flush() end
end

local state = { hosting = false, joining = false, target = nil, spawned = {} }

-- UE4SS timers (ExecuteWithDelay / LoopAsync) run on their own thread. Anything that touches
-- game objects (spawn, possess, level streaming, even reading actors) must hop to the game thread.
-- sdmp.ini next to this script: host_steamid / host_ip
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

local function gt(fn)
  return function(...)
    local args = { ... }
    ExecuteInGameThread(function()
      local ok, err = pcall(fn, table.unpack(args))
      if not ok then print("[SDMP] game-thread error: " .. tostring(err) .. "\n") end
    end)
  end
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
  local pend = liveInstances("PendingNetGame")
  if #pend > 0 then
    local d = "nil"; pcall(function() local nd = pend[1].NetDriver; d = valid(nd) and nd:GetClass():GetFName():ToString() or "nil" end)
    s = s .. " pending=" .. #pend .. "(driver=" .. d .. ")"
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
  -- spawn next to the host's pawn, else at origin-ish
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

local function spawnMissing()
  if isClient() then return end
  local hostPc = UEHelpers.GetPlayerController()
  local okh, hostPawn = pcall(function() return hostPc.Pawn end)
  if not (okh and valid(hostPawn)) then return end  -- host not in world yet; wait
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
      local function try(f, dflt) local ok, v = pcall(f); if ok then return v end; return dflt .. ":" .. tostring(v):sub(1, 40) end
      -- loaded levels: the ULevel's outer is its package, e.g. "Package /Game/Levels/MainMenu"
      local pkg = try(function() local lvl = ls:GetLoadedLevel(); if valid(lvl) then return lvl:GetOuter():GetFullName():gsub("^Package ", "") end; return "?" end, "?")
      if pkg:sub(1, 1) == "?" or pkg == "None" then pkg = try(function() return ls.WorldAsset:ToString() end, "?") end
      if pkg:sub(1, 1) == "?" or pkg == "None" then pkg = ls:GetFullName():gsub("^.*:", "") end
      local loaded = try(function() return ls:IsLevelLoaded() end, "E")
      local visible = try(function() return ls:IsLevelVisible() end, "E")
      local sbl = try(function() return ls:ShouldBeLoaded() end, "E")
      local sbv = try(function() return ls.bShouldBeVisible end, "E")
      fn(ls, pkg, loaded == true, visible == true, sbl, sbv)
    end
  end)
end

local function logLevels(tag)
  eachStreamingLevel(function(ls, pkg, loaded, visible, sbl, sbv)
    log(string.format("LEVELS[%s] %s loaded=%s visible=%s shouldLoad=%s shouldVis=%s", tag, pkg, tostring(loaded), tostring(visible), tostring(sbl), tostring(sbv)))
  end)
  local n = 0
  local widgets = FindAllOf("UserWidget")
  if widgets then for _, wdg in ipairs(widgets) do
    if valid(wdg) and not wdg:GetFullName():find("Default__", 1, true) then
      local inVp = false; pcall(function() inVp = wdg:IsInViewport() end)
      if inVp then n = n + 1; log("WIDGET[" .. tag .. "] " .. wdg:GetClass():GetFName():ToString() .. " " .. short(wdg)) end
    end
  end end
  log("WIDGETS[" .. tag .. "] in viewport: " .. n)
end
RegisterConsoleCommandHandler("sdmp_levels", function() logLevels("manual"); return true end)

-- client: once connected with a pawn, kill the menu UI and give input back to the game
local MENU_WIDGETS = { MenuWidget_C = true, LoadingScreenWidget_C = true, MainMenu_C = true }
local function clientTakeControl()
  local pc = UEHelpers.GetPlayerController()
  local ok, pawn = pcall(function() return pc.Pawn end)
  if not (ok and valid(pawn)) then return end
  -- the game's single-player start flow also runs on a client when the world level streams in, spawning a
  -- local, non-networked player. Locally spawned actors on a client have local role Authority (3);
  -- real networked pawns are AutonomousProxy (2) or SimulatedProxy (1). Destroy the phantoms.
  for _, p in ipairs(liveInstances("BP_PlayerCharacter_C")) do
    local okr, role = pcall(function() return p:GetLocalRole() end)
    if okr and tonumber(role) == 3 then
      log("client: destroying locally spawned phantom pawn " .. short(p))
      pcall(function() p:K2_DestroyActor() end)
    end
  end
  local removed = 0
  local widgets = FindAllOf("UserWidget")
  if widgets then for _, wdg in ipairs(widgets) do
    if valid(wdg) and not wdg:GetFullName():find("Default__", 1, true) then
      local cls = wdg:GetClass():GetFName():ToString()
      local inVp = false; pcall(function() inVp = wdg:IsInViewport() end)
      if MENU_WIDGETS[cls] and inVp then
        local okr = pcall(function() wdg:RemoveFromParent() end)
        if okr then removed = removed + 1; log("client: removed menu widget " .. cls) end
      end
    end
  end end
  if removed > 0 or not state.inputFixed then
    local okm, errm = pcall(function()
      local wbl = StaticFindObject("/Script/UMG.Default__WidgetBlueprintLibrary")
      wbl:SetInputMode_GameOnly(pc, false)
      pc.bShowMouseCursor = false
      log("client: input mode set to game-only")
    end)
    if not okm then log("client: input mode error: " .. tostring(errm)) end
    state.inputFixed = true
  end
end

-- client: make sure the world sub-level streams in and the menu sub-level goes away
local function ensureLevelLoaded()
  eachStreamingLevel(function(ls, pkg, loaded, visible, sbl, sbv)
    if pkg:find(LEVEL_NAME, 1, true) and not (loaded and visible) then
      log("client: requesting stream-in of " .. pkg .. " (loaded=" .. tostring(loaded) .. " visible=" .. tostring(visible) .. ")")
      pcall(function() ls:SetShouldBeLoaded(true); ls:SetShouldBeVisible(true) end)
    elseif pkg:find("MainMenu", 1, true) and (loaded or visible) then
      log("client: unloading " .. pkg)
      pcall(function() ls:SetShouldBeVisible(false); ls:SetShouldBeLoaded(false) end)
    end
  end)
end

-- ---------- net driver selection ----------
-- The game's GameNetDriver is SteamSockets (fallback IpNetDriver). Rewrite the definition at runtime so
-- the next `open` uses plain IP while Steam stays running (needs VPN or port-forward UDP 7777 on the host).
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
local DRIVER_STEAM = "/Script/SteamSockets.SteamSocketsNetDriver"
local DRIVER_IP = "/Script/OnlineSubsystemUtils.IpNetDriver"
RegisterConsoleCommandHandler("sdmp_driver", function(full, params)
  local which = (params[1] or ""):lower()
  if which == "ip" then setNetDriver(DRIVER_IP) elseif which == "steam" then setNetDriver(DRIVER_STEAM) else log("usage: sdmp_driver ip|steam") end
  return true
end)

-- ---------- commands (forward declarations; defined below) ----------
local cmdHost, cmdJoin

-- ---------- main menu buttons ----------
-- Two instances of the game's own ButtonWidget_C are added under the Quit button of MenuWidget_C.
-- Clicks are detected by hooking ButtonWidget_C's click event and comparing the instance.
local BTN_CLASS = "/Game/UI/Menus/ButtonWidget.ButtonWidget_C"
local menuUI = { host = nil, join = nil, menu = nil }

local function setButtonText(w, label)
  pcall(function() w.Text = FText(label) end)
  pcall(function() w.ButtonText:SetText(FText(label)) end)
end

local function findMenuWidget()
  local widgets = FindAllOf("UserWidget")
  if not widgets then return nil end
  for _, w in ipairs(widgets) do
    if valid(w) and not w:GetFullName():find("Default__", 1, true) and w:GetClass():GetFName():ToString() == "MenuWidget_C" then
      local inVp = false; pcall(function() inVp = w:IsInViewport() end)
      if inVp then return w end
    end
  end
  return nil
end

local function makeMenuButton(menu, label, refButton, index)
  local cls = StaticFindObject(BTN_CLASS)
  if not valid(cls) then error("ButtonWidget_C class not loaded") end
  local wbl = StaticFindObject("/Script/UMG.Default__WidgetBlueprintLibrary")
  local w = wbl:Create(UEHelpers.GetWorld(), cls, UEHelpers.GetPlayerController())
  if not valid(w) then error("Create() returned nothing") end
  local parent = refButton:GetParent()
  local pname = valid(parent) and parent:GetClass():GetFName():ToString() or "?"
  if pname == "CanvasPanel" then
    local refSlot = refButton.Slot
    local pos, size = refSlot:GetPosition(), refSlot:GetSize()
    local slot = parent:AddChildToCanvas(w)
    slot:SetAutoSize(false)
    slot:SetPosition({ X = pos.X, Y = pos.Y + (size.Y + 6) * index })
    slot:SetSize({ X = size.X, Y = size.Y })
    log(string.format("menu: added '%s' at %.0f,%.0f size %.0fx%.0f (ref %s)", label, pos.X, pos.Y + (size.Y + 6) * index, size.X, size.Y, refButton:GetFName():ToString()))
  elseif pname == "VerticalBox" then
    parent:AddChildToVerticalBox(w)
    log("menu: added '" .. label .. "' to vertical box")
  else
    w:AddToViewport(50)
    log("menu: parent is " .. pname .. ", added '" .. label .. "' to viewport instead")
  end
  setButtonText(w, label)
  return w
end

local function injectMenuButtons()
  local nd = netDriver()
  if nd then
    -- hosting (or joined): show a status line on the rebuilt menu instead of the buttons
    if isClient() then return end
    local menu = findMenuWidget()
    if not menu then return end
    if menuUI.statusMenu and valid(menuUI.statusMenu) and menuUI.statusMenu:GetAddress() == menu:GetAddress() and valid(menuUI.status) then return end
    local ok, err = pcall(function()
      menuUI.status = makeMenuButton(menu, "MP: HOSTING OK - now click New or Load", menu.Quit, 1)
      menuUI.statusMenu = menu
    end)
    if not ok then log("menu: status inject failed: " .. tostring(err)) end
    return
  end
  local menu = findMenuWidget()
  if not menu then
    if not menuUI.loggedNoMenu then menuUI.loggedNoMenu = true
      local n = 0; local ws = FindAllOf("UserWidget"); if ws then for _, w in ipairs(ws) do if valid(w) and not w:GetFullName():find("Default__", 1, true) then n = n + 1; log("menu: widget seen: " .. w:GetClass():GetFName():ToString()) end end end
      log("menu: MenuWidget_C not in viewport yet (" .. n .. " widgets alive)")
    end
    return
  end
  if menuUI.menu and valid(menuUI.menu) and menuUI.menu:GetAddress() == menu:GetAddress() and valid(menuUI.host) and valid(menuUI.join) then return end
  local ok, err = pcall(function()
    local ref = menu.Quit
    if not valid(ref) then error("Quit button not found on menu") end
    menuUI.host = makeMenuButton(menu, "MP: HOST", ref, 1)
    menuUI.join = makeMenuButton(menu, "MP: JOIN " .. (readConfig().host_ip or "?"), ref, 2)
    menuUI.menu = menu
  end)
  if not ok then log("menu: inject failed: " .. tostring(err)) end
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

ExecuteWithDelay(12000, gt(function()
  local ok, err = pcall(function()
    RegisterHook(BTN_CLASS .. ":BndEvt__ButtonWidget_Button_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature", function(ctx)
      local w; pcall(function() w = ctx:get() end)
      onMenuButtonClicked(w)
    end)
  end)
  log(ok and "menu: click hook installed" or ("menu: click hook failed: " .. tostring(err):sub(1, 100)))
end))
LoopAsync(2000, function()
  ExecuteInGameThread(function()
    local ok, err = pcall(injectMenuButtons)
    if not ok and not menuUI.loggedErr then menuUI.loggedErr = true; log("menu: inject loop error: " .. tostring(err)) end
  end)
  return false
end)

-- ---------- commands ----------
cmdHost = function()
  local nd = netDriver()
  if nd and not isClient() then
    log("sdmp_host: already hosting, not re-opening (press F6 for status)")
    status("host")
    return true
  end
  log("sdmp_host: issuing open PersistentLevel?listen")
  consoleCmd("open PersistentLevel?listen")
  state.hosting = true
  state.hostAttempts = (state.hostAttempts or 0) + 1
  ExecuteWithDelay(8000, gt(function()
    status("host")
    local nd = netDriver()
    if nd and not isClient() then
      log("HOSTING OK: listen server is up (" .. nd:GetClass():GetFName():ToString() .. "). Now click New Game / Continue.")
      if valid(menuUI.host) then setButtonText(menuUI.host, "MP: HOSTING OK - now click New Game / Continue") end
      state.hostAttempts = 0
    elseif state.hostAttempts < 4 then
      log("listen did not come up, retrying in 5s (attempt " .. (state.hostAttempts + 1) .. "/4)")
      ExecuteWithDelay(5000, function() if state.useIpDriver then setNetDriver(DRIVER_IP) end; cmdHost() end)
    else
      log("HOSTING FAILED after 4 attempts. Restart the game, wait on the main menu 60s, try again.")
      state.hostAttempts = 0
    end
  end))
  return true
end

cmdJoin = function(target, viaIp)
  if not target or target == "" then log("usage: sdmp_join <SteamID64>   or   sdmp_join_ip <ip[:port]>"); return true end
  local url = viaIp and target or ("steam." .. target)
  log("sdmp_join: open " .. url)
  state.joining = true; state.target = url
  consoleCmd("open " .. url)
  for _, d in ipairs({ 5000, 10000, 20000, 40000 }) do ExecuteWithDelay(d, gt(function() status("join+" .. (d / 1000) .. "s") end)) end
  ExecuteWithDelay(12000, gt(function() logLevels("join+12s") end))
  ExecuteWithDelay(45000, gt(function() logLevels("join+45s") end))
  return true
end

RegisterConsoleCommandHandler("sdmp_host", function() state.useIpDriver = true; setNetDriver(DRIVER_IP); return cmdHost() end)
RegisterConsoleCommandHandler("sdmp_host_steam", function() state.useIpDriver = false; setNetDriver(DRIVER_STEAM); return cmdHost() end)
RegisterConsoleCommandHandler("sdmp_host_ip", function() state.useIpDriver = true; setNetDriver(DRIVER_IP); return cmdHost() end)
RegisterConsoleCommandHandler("sdmp_join", function(full, params) return cmdJoin(params[1], false) end)
RegisterConsoleCommandHandler("sdmp_join_ip", function(full, params) setNetDriver(DRIVER_IP); return cmdJoin(params[1], true) end)
RegisterConsoleCommandHandler("sdmp_status", function() status("manual"); return true end)
RegisterConsoleCommandHandler("sdmp_spawn", function() state.spawned = {}; spawnMissing(); return true end)
RegisterKeyBind(Key.F7, {}, function() log("F7: host with IP driver"); state.useIpDriver = true; setNetDriver(DRIVER_IP); cmdHost() end)
RegisterKeyBind(Key.F7, {ModifierKey.CONTROL}, function() log("Ctrl+F7: host with Steam Sockets driver"); state.useIpDriver = false; setNetDriver(DRIVER_STEAM); cmdHost() end)
RegisterKeyBind(Key.F6, {}, function() status("F6") end)

-- no-console path: sdmp.ini next to this script holds the host's SteamID / IP; F8 joins it (readConfig is defined near the top)
RegisterKeyBind(Key.F8, {}, function()
  local cfg = readConfig()
  if cfg.host_steamid then log("F8: joining host_steamid from sdmp.ini"); cmdJoin(cfg.host_steamid, false)
  elseif cfg.host_ip then log("F8: joining host_ip from sdmp.ini"); cmdJoin(cfg.host_ip, true)
  else log("F8: no host_steamid or host_ip in sdmp.ini") end
end)
RegisterKeyBind(Key.F9, {}, function()
  local cfg = readConfig()
  if cfg.host_ip then log("F9: joining host_ip from sdmp.ini (IP driver)"); setNetDriver(DRIVER_IP); cmdJoin(cfg.host_ip, true)
  else log("F9: no host_ip in sdmp.ini") end
end)
RegisterKeyBind(Key.F7, {ModifierKey.SHIFT}, function() log("Shift+F7: host with IP driver"); state.useIpDriver = true; setNetDriver(DRIVER_IP); cmdHost() end)

-- ---------- hooks + background loop ----------
pcall(function()
  RegisterHook("/Script/Engine.GameModeBase:K2_PostLogin", function(ctx, newPlayer)
    local who = "?"; pcall(function() who = short(newPlayer:get()) end)
    log("PostLogin: " .. who)
    ExecuteWithDelay(3000, gt(spawnMissing))
    ExecuteWithDelay(10000, gt(spawnMissing))
  end)
end)
pcall(function()
  RegisterHook("/Script/Engine.GameModeBase:K2_OnLogout", function(ctx, exiting)
    local who = "?"; pcall(function() who = short(exiting:get()) end)
    log("Logout: " .. who); state.spawned[who] = nil
  end)
end)

-- connection-failure diagnostics (client side)
for _, fn in ipairs({
  "/Script/Engine.PlayerController:ClientReturnToMainMenuWithTextReason",
  "/Script/Engine.PlayerController:ClientTravelInternal",
  "/Script/Engine.PlayerController:ClientSetHUD",
  "/Script/Engine.PlayerController:ClientRestart",
  "/Script/Engine.PlayerController:ClientGotoState",
}) do
  pcall(function()
    RegisterHook(fn, function(ctx, ...)
      local parts = {}
      for _, a in ipairs({...}) do pcall(function() local v = a:get(); local ok, s = pcall(function() return v:ToString() end); parts[#parts+1] = ok and s or tostring(v) end) end
      log("NET-EVENT " .. fn:gsub("^.*:", "") .. " [" .. table.concat(parts, ", ") .. "]")
    end)
  end)
end

LoopAsync(5000, function()
  ExecuteInGameThread(function()
    if state.hosting then pcall(spawnMissing) end
    if state.joining and isClient() then pcall(ensureLevelLoaded); pcall(clientTakeControl) end
  end)
  return false
end)

-- trace the game's own start/spawn flow so we can see what runs on a client after joining.
-- Blueprint classes are not loaded when this script starts, so register after a delay, on the game thread.
ExecuteWithDelay(12000, gt(function()
  for _, fn in ipairs({
    "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Event_LoadLevel",
    "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Survival_SpawnPlayer",
    "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:GameMode_SpawnPlayer",
    "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Survival_Respawn",
    "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C:ReceivePossess",
    "/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C:ReceiveBeginPlay",
  }) do
    local ok, err = pcall(function()
      RegisterHook(fn, function(ctx, ...)
        local who = ""; pcall(function() who = short(ctx:get()) end)
        local parts = {}
        for _, a in ipairs({...}) do pcall(function() local v = a:get(); local ok2, s = pcall(function() return v:GetFullName() end); parts[#parts+1] = ok2 and s or tostring(v) end) end
        log("GAME-FLOW " .. fn:gsub("^.*:", "") .. " self=" .. who .. " [" .. table.concat(parts, ", ") .. "]" .. (isClient() and " (CLIENT)" or ""))
      end)
    end)
    if not ok then log("hook failed: " .. fn .. " : " .. tostring(err):sub(1, 80)) end
  end
end))

-- sdmp_spawntest: (host, in world) spawn an unpossessed player pawn next to you to validate the spawn path
local function spawnTest()
  local world = UEHelpers.GetWorld()
  local cls = StaticFindObject(PLAYER_CLASS)
  local hp = UEHelpers.GetPlayerController().Pawn
  if not valid(hp) then log("spawntest: no host pawn yet"); return false end
  local l = hp:K2_GetActorLocation()
  local ok, pawn = pcall(function() return world:SpawnActor(cls, { X = l.X + 250, Y = l.Y, Z = l.Z + 50 }, { Pitch = 0, Yaw = 0, Roll = 0 }) end)
  log(string.format("spawntest: ok=%s result=%s", tostring(ok), ok and short(pawn) or tostring(pawn)))
  if ok and valid(pawn) then
    pcall(function() local l2 = pawn:K2_GetActorLocation(); log(string.format("spawntest: pawn at %.0f %.0f %.0f, host at %.0f %.0f %.0f", l2.X, l2.Y, l2.Z, l.X, l.Y, l.Z)) end)
    local okc, ctrl = pcall(function() return pawn.Controller end)
    log("spawntest: pawn.Controller=" .. ((okc and valid(ctrl)) and short(ctrl) or "nil") .. " (expected nil, unpossessed)")
  end
  return true
end
RegisterConsoleCommandHandler("sdmp_spawntest", function() spawnTest(); return true end)

-- dev: env SDMP_DEV=host        -> auto-host at 35s, then enter the world via the game's own Event_LoadLevel at 50s
--      env SDMP_DEV=join:<url>  -> auto sdmp_join_ip <url> at 45s   (two-instance loopback test on one PC)
do local role = os.getenv("SDMP_DEV")
  if role and role ~= "" then
    logf = io.open("SDMP_" .. role:gsub("[^%w]", "_") .. ".log", "a")
    log("SDMP_DEV=" .. role)
    if role == "host" or role == "hostip" then
      ExecuteWithDelay(35000, gt(function() if role == "hostip" then state.useIpDriver = true; setNetDriver(DRIVER_IP) end; cmdHost() end))
      ExecuteWithDelay(50000, gt(function()
        local ok, err = pcall(function() UEHelpers.GetGameInstance():Event_LoadLevel(FName(LEVEL_NAME)) end)
        log("dev host: Event_LoadLevel(" .. LEVEL_NAME .. ") ok=" .. tostring(ok) .. " " .. tostring(err))
      end))
      ExecuteWithDelay(75000, gt(function() logLevels("host+75s") end))
      LoopAsync(15000, function() ExecuteInGameThread(function() status("dev-host") end); return false end)
    elseif role:sub(1, 5) == "join:" then
      ExecuteWithDelay(45000, gt(function() cmdJoin(role:sub(6), true) end))
      LoopAsync(15000, function() ExecuteInGameThread(function() status("dev-join") end); return false end)
    elseif role:sub(1, 7) == "joinip:" then
      ExecuteWithDelay(45000, gt(function() setNetDriver(DRIVER_IP); cmdJoin(role:sub(8), true) end))
      LoopAsync(15000, function() ExecuteInGameThread(function() status("dev-join") end); return false end)
    end
  end
end

-- dev convenience: if <Win64>/SDMP_autohost.txt exists, host automatically 35s after boot,
-- then run one spawn test as soon as the host has a pawn (i.e. after New Game / Continue)
do local f = io.open("SDMP_autohost.txt", "r"); if f then
  local mode = (f:read("*l") or ""):gsub("%s", ""); f:close()
  local delay = tonumber(mode:match("(%d+)")) or 35
  local useIp = mode:find("ip") ~= nil
  log("SDMP_autohost.txt present: hosting in " .. delay .. "s (ip=" .. tostring(useIp) .. "), spawntest after New Game")
  ExecuteWithDelay(delay * 1000, gt(function() if useIp then state.useIpDriver = true; setNetDriver(DRIVER_IP) end; cmdHost() end))
  local done = false
  LoopAsync(5000, function()
    if done then return true end
    ExecuteInGameThread(function()
      if done then return end
      local ok, hp = pcall(function() return UEHelpers.GetPlayerController().Pawn end)
      if ok and valid(hp) then done = true; status("in-world"); spawnTest() end
    end)
    return false
  end)
end end

do local cfg = readConfig(); log("sdmp.ini: host_steamid=" .. tostring(cfg.host_steamid) .. " host_ip=" .. tostring(cfg.host_ip)) end
log("SDMP v" .. VERSION .. " loaded. Keys: F7=host  F8=join host from sdmp.ini  F6=status. Console: sdmp_host, sdmp_join <SteamID64>, sdmp_status")
