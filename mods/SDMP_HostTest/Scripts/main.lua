-- SDMP_HostTest: Phase 1. From the main menu, issue `open PersistentLevel?listen`
-- and report what the engine did (net driver instances, world, game mode, pawns).
-- Output: <Win64>/SDMP_hosttest.txt
local UEHelpers = require("UEHelpers")
local START_DELAY_MS = 35000
local out = {}
local function w(s) out[#out+1] = os.date("%H:%M:%S ") .. s; print("[SDMP_HostTest] " .. s .. "\n") end
local function flush()
  local f = io.open("SDMP_hosttest.txt", "w"); f:write(table.concat(out, "\n")); f:close()
end

local function listInstances(className)
  local objs = FindAllOf(className)
  local n = 0
  if objs then
    for _, o in ipairs(objs) do
      local name = o:GetFullName()
      if not name:find("Default__", 1, true) then n = n + 1; w("    " .. className .. ": " .. name) end
    end
  end
  if n == 0 then w("    " .. className .. ": (no live instances)") end
end

local function snapshot(tag)
  w("---- snapshot: " .. tag)
  pcall(function()
    local world = UEHelpers.GetWorld()
    w("  World: " .. (world and world:IsValid() and world:GetFullName() or "nil"))
    if world and world:IsValid() then
      local ok, nd = pcall(function() return world.NetDriver end)
      w("  World.NetDriver: " .. ((ok and nd and nd:IsValid()) and nd:GetFullName() or "nil"))
      local ok2, ws = pcall(function() return world.URL end)
    end
  end)
  pcall(function()
    local gm = UEHelpers.GetGameModeBase()
    w("  GameMode: " .. (gm and gm:IsValid() and gm:GetFullName() or "nil"))
    if gm and gm:IsValid() then
      local ok, np = pcall(function() return gm.NumPlayers end); if ok then w("  GameMode.NumPlayers: " .. tostring(np)) end
    end
  end)
  pcall(function()
    local gs = UEHelpers.GetGameStateBase()
    w("  GameState: " .. (gs and gs:IsValid() and gs:GetFullName() or "nil"))
    if gs and gs:IsValid() then
      local ok, arr = pcall(function() return gs.PlayerArray end); if ok and arr then w("  GameState.PlayerArray: " .. tostring(#arr)) end
    end
  end)
  pcall(function()
    local pc = UEHelpers.GetPlayerController()
    w("  PlayerController: " .. (pc and pc:IsValid() and pc:GetFullName() or "nil"))
    if pc and pc:IsValid() then
      local ok, pawn = pcall(function() return pc.Pawn end)
      w("  PC.Pawn: " .. ((ok and pawn and pawn:IsValid()) and pawn:GetFullName() or "nil"))
    end
  end)
  w("  Net driver instances:")
  for _, c in ipairs({"SteamSocketsNetDriver", "IpNetDriver", "NetDriver", "NetConnection", "SteamSocketsNetConnection", "IpConnection"}) do listInstances(c) end
  w("  Player pawns:")
  listInstances("BP_PlayerCharacter_C")
  flush()
end

ExecuteWithDelay(START_DELAY_MS, function()
  w("Phase 1 host test start")
  snapshot("before open (main menu)")
  local pc = UEHelpers.GetPlayerController()
  if not (pc and pc:IsValid()) then w("ERROR no player controller"); flush(); return end
  w("Issuing console command: open PersistentLevel?listen")
  local ok, err = pcall(function()
    local ksl = UEHelpers.GetKismetSystemLibrary()
    ksl:ExecuteConsoleCommand(UEHelpers.GetWorld(), "open PersistentLevel?listen", pc)
  end)
  w("ExecuteConsoleCommand ok=" .. tostring(ok) .. " err=" .. tostring(err))
  flush()
  ExecuteWithDelay(20000, function() snapshot("+20s after open") end)
  ExecuteWithDelay(60000, function() snapshot("+60s after open") end)
  ExecuteWithDelay(120000, function() snapshot("+120s after open"); w("DONE"); flush() end)
end)
w("armed")
