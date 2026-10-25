-- SDMP_FlowTrace: log the game's own level-load and player-spawn flow so we know
-- how "New Game" / "Continue" interact with a listen server.
-- Also issues `open PersistentLevel?listen` 35s after boot (Phase 1 host setup),
-- then logs a net snapshot every 30s. Output: <Win64>/SDMP_flow.txt
local UEHelpers = require("UEHelpers")
local out = {}
local function w(s) out[#out+1] = os.date("%H:%M:%S ") .. s; print("[SDMP_Flow] " .. s .. "\n")
  local f = io.open("SDMP_flow.txt", "w"); f:write(table.concat(out, "\n")); f:close() end

local HOOKS = {
  "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Event_LoadLevel",
  "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:SmoothLoadLevel",
  "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:GameMode_SpawnPlayer",
  "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Survival_SpawnPlayer",
  "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Survival_Respawn",
  "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:Debug_SpawnPlayer",
  "/Game/Blueprints/SD_GameInstance.SD_GameInstance_C:PlayerSpawnedInLevel",
  "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C:ReceivePossess",
  "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C:LoadGameFromSlot",
  "/Game/Blueprints/BP_PlayerController.BP_PlayerController_C:SaveGameToSlot",
  "/Game/Blueprints/BP_SurroundeadGameMode.BP_SurroundeadGameMode_C:ReceiveBeginPlay",
  "/Game/Blueprints/BP_SurroundeadGameMode.BP_SurroundeadGameMode_C:ReceiveEndPlay",
  "/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C:ReceiveBeginPlay",
  "/Script/Engine.GameplayStatics:OpenLevel",
  "/Script/Engine.GameplayStatics:OpenLevelBySoftObjectPtr",
  "/Script/Engine.GameplayStatics:GetStreamingLevel",
  "/Script/Engine.GameplayStatics:LoadStreamLevel",
  "/Script/Engine.GameplayStatics:UnloadStreamLevel",
  "/Script/Engine.GameplayStatics:LoadStreamLevelBySoftObjectPtr",
  "/Script/Engine.GameMode:RestartPlayer",
  "/Script/Engine.GameModeBase:RestartPlayer",
  "/Script/Engine.GameModeBase:K2_PostLogin",
  "/Script/Engine.GameModeBase:K2_OnLogout",
}

local function argsToString(...)
  local parts = {}
  for i, a in ipairs({...}) do
    local ok, s = pcall(function()
      local v = a:get()
      if type(v) == "userdata" then
        local ok2, s2 = pcall(function() return v:GetFullName() end)
        if ok2 then return s2 end
        local ok3, s3 = pcall(function() return v:ToString() end)
        if ok3 then return s3 end
        return tostring(v)
      end
      return tostring(v)
    end)
    parts[#parts+1] = ok and s or "?"
  end
  return table.concat(parts, ", ")
end

local function install()
  for _, fn in ipairs(HOOKS) do
    local ok, err = pcall(function()
      RegisterHook(fn, function(ctx, ...)
        local who = ""
        pcall(function() who = ctx:get():GetFullName() end)
        w("CALL " .. fn:gsub("^.*:", "") .. "  self=" .. who .. "  args=[" .. argsToString(...) .. "]")
      end)
    end)
    w((ok and "hooked " or ("HOOK FAILED " .. tostring(err) .. " ")) .. fn)
  end
end

local function netSnapshot(tag)
  local s = "NET[" .. tag .. "]"
  pcall(function()
    local world = UEHelpers.GetWorld()
    local nd = world.NetDriver
    s = s .. " world=" .. world:GetFullName():gsub("^World ", "") .. " driver=" .. ((nd and nd:IsValid()) and nd:GetFullName():gsub("^%S+ ", "") or "nil")
  end)
  pcall(function()
    local pc = UEHelpers.GetPlayerController(); local pawn = pc.Pawn
    s = s .. " pawn=" .. ((pawn and pawn:IsValid()) and pawn:GetFullName():gsub("^%S+ ", "") or "nil")
  end)
  pcall(function() s = s .. " players=" .. tostring(#UEHelpers.GetGameStateBase().PlayerArray) end)
  local conns = FindAllOf("NetConnection"); local n = 0
  if conns then for _, c in ipairs(conns) do if not c:GetFullName():find("Default__", 1, true) then n = n + 1 end end end
  s = s .. " connections=" .. n
  w(s)
end

ExecuteWithDelay(10000, function()
  install()
  ExecuteWithDelay(25000, function()
    netSnapshot("before listen")
    local pc = UEHelpers.GetPlayerController()
    UEHelpers.GetKismetSystemLibrary():ExecuteConsoleCommand(UEHelpers.GetWorld(), "open PersistentLevel?listen", pc)
    w("issued: open PersistentLevel?listen  -- now click New Game / Continue in the game")
    ExecuteWithDelay(15000, function() netSnapshot("after listen") end)
    LoopAsync(30000, function() netSnapshot("periodic"); return false end)
  end)
end)
w("armed")
