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
local VERSION = "0.1.1"
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

-- ---------- commands ----------
local function cmdHost()
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

local function cmdJoin(target, viaIp)
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

-- no-console path: sdmp.ini next to this script holds the host's SteamID / IP; F8 joins it
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
    if state.joining and isClient() then pcall(ensureLevelLoaded) end
  end)
  return false
end)

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
