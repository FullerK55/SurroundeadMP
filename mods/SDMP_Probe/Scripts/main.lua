-- SDMP_Probe: writes a report of network-relevant flags for key game classes.
-- Output: <game Win64 dir>/SDMP_probe.txt  (Lua cwd is the exe directory)
local DELAY_MS = 30000
local FUNC_Net, FUNC_NetReliable, FUNC_NetMulticast, FUNC_NetServer, FUNC_NetClient = 0x40, 0x80, 0x4000, 0x200000, 0x1000000
local CPF_Net, CPF_RepNotify = 0x20, 0x100000000

local CLASSES = {
  "/Script/Engine.Character",  -- sanity check: must show replicated props (ReplicatedMovement etc.)
  "/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C",
  "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C",
  "/Game/Blueprints/BP_SurroundeadGameMode.BP_SurroundeadGameMode_C",
  "/Game/Blueprints/BP_SurroundeadGameState.BP_SurroundeadGameState_C",
  "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C",
  "/Game/JigSInventory/Jigsaw/Components/BP_JigMultiplayer.BP_JigMultiplayer_C",
  "/Game/Inventory/Items/Pickups/Weapons/Firearms/BP_FirearmPickup.BP_FirearmPickup_C",
  "/Game/SmartAI/Blueprints/AI/AICharacters/BP_MasterAICharacter.BP_MasterAICharacter_C",
  "/Game/AI/Zombies/BP_Zombie.BP_Zombie_C",
  "/Game/AI/Zombies/BP_ZombieAIController.BP_ZombieAIController_C",
  "/Game/Blueprints/BuildingSystem/Actors/Buildable_MASTER.Buildable_MASTER_C",
  "/Game/Blueprints/Vehicles/BP_VehicleMaster.BP_VehicleMaster_C",
  "/Game/Blueprints/HUD_Game.HUD_Game_C",
}

local out = {}
local function w(s) out[#out+1] = s end

local function flagstr(f)
  local t = {}
  if f & FUNC_Net ~= 0 then t[#t+1] = "Net" end
  if f & FUNC_NetReliable ~= 0 then t[#t+1] = "Reliable" end
  if f & FUNC_NetServer ~= 0 then t[#t+1] = "Server" end
  if f & FUNC_NetClient ~= 0 then t[#t+1] = "Client" end
  if f & FUNC_NetMulticast ~= 0 then t[#t+1] = "Multicast" end
  return table.concat(t, "|")
end

local function probeClass(cls, label)
  w("")
  w("==== " .. label)
  local cdoPath = cls:GetFullName():gsub("^%S+ ", ""):gsub("%.([^%.]+)$", ".Default__%1")
  local ok, cdo = pcall(function() return StaticFindObject(cdoPath) end)
  if ok and cdo and cdo:IsValid() then
    for _, p in ipairs({"bReplicates", "bReplicateMovement", "bAlwaysRelevant", "bOnlyRelevantToOwner", "bNetLoadOnClient", "NetUpdateFrequency", "bReplicateUsingRegisteredSubObjectList"}) do
      local ok2, v = pcall(function() return cdo[p] end)
      if ok2 and v ~= nil then w(string.format("  CDO.%s = %s", p, tostring(v))) end
    end
  else
    w("  (CDO not found: " .. cdoPath .. ")")
  end
  local nFn, nNet = 0, 0
  pcall(function()
    cls:ForEachFunction(function(fn)
      nFn = nFn + 1
      local f = fn:GetFunctionFlags()
      if f & (FUNC_Net | FUNC_NetServer | FUNC_NetClient | FUNC_NetMulticast) ~= 0 then
        nNet = nNet + 1
        w(string.format("  RPC  %-50s %s", fn:GetFName():ToString(), flagstr(f)))
      end
    end)
  end)
  local nProp, nRep = 0, 0
  pcall(function()
    cls:ForEachProperty(function(prop)
      nProp = nProp + 1
      local okf, pf = pcall(function() return prop:GetPropertyFlags() end)
      if okf and pf and (pf & (CPF_Net | CPF_RepNotify)) ~= 0 then
        nRep = nRep + 1
        w(string.format("  REP  %-50s %s%s", prop:GetFName():ToString(), prop:GetClass():GetFName():ToString(), (pf & CPF_RepNotify ~= 0) and " (RepNotify)" or ""))
      end
    end)
  end)
  w(string.format("  summary: %d functions (%d net RPC), %d properties (%d replicated)", nFn, nNet, nProp, nRep))
end

ExecuteWithDelay(DELAY_MS, function()
  w("SDMP probe " .. os.date())
  local ge = StaticFindObject("/Script/Engine.Default__GameEngine")
  if ge and ge:IsValid() then
    pcall(function()
      local defs = ge.NetDriverDefinitions
      w("GameEngine.NetDriverDefinitions count = " .. tostring(#defs))
      defs:ForEach(function(i, el)
        local d = el:get()
        w(string.format("  [%d] %s -> %s (fallback %s)", i, d.DefName:ToString(), d.DriverClassName:ToString(), d.DriverClassNameFallback:ToString()))
      end)
    end)
  end
  for _, path in ipairs(CLASSES) do
    local c = StaticFindObject(path)
    if c and c:IsValid() then probeClass(c, path) else w("NOT FOUND: " .. path) end
  end
  local f = io.open("SDMP_probe.txt", "w")
  f:write(table.concat(out, "\n")); f:close()
  print("[SDMP_Probe] DONE wrote SDMP_probe.txt\n")
end)
print("[SDMP_Probe] armed\n")
