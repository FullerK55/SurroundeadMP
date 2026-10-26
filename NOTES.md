# SurrounDead multiplayer mod: research notes

Private, non-commercial mod so a group of friends who all own SurrounDead can play together.

## Game facts (verified 2026-10-25)

| Item | Value |
|---|---|
| Install | `C:\Program Files (x86)\Steam\steamapps\common\SurrounDead` |
| Steam appid | 1645820 |
| Engine | Unreal Engine 5.3 (CL 29314046), Shipping build |
| Exe | `SurrounDead\Binaries\Win64\SurrounDead-Win64-Shipping.exe` |
| Pak | `SurrounDead\Content\Paks\SurrounDead-Windows.pak`, v11, Oodle, **not encrypted**, no IoStore |
| Native game module | `SurrounDead`: 3 tiny function libraries. **All gameplay is Blueprint.** |
| Levels | `/Game/Levels/MainMenu`, `/Game/Levels/PersistentLevel` (the world; uses level streaming) |
| Game mode | `BP_SurroundeadGameMode_C` (AGameModeBase) |
| Game state | `BP_SurroundeadGameState_C` (bReplicates, bAlwaysRelevant) |
| Game instance | `SD_GameInstance_C` (owns `SteamCoreSubsystem`, has `Event_LoadLevel`, `GameMode_SpawnPlayer`, `Survival_Respawn`) |
| Player pawn | `BP_PlayerCharacter_C` : `BP_MasterPlayer_C` : ACharacter |
| Player controller | `BP_PlayerController_C` : `BP_MasterPlayerController_C` |
| Zombies | `BP_Zombie_C` : `BP_MasterAICharacter_C` (SmartAI asset), `BP_ZombieAIController_C` |
| Inventory | Jigsaw Inventory System (JSI), component `BP_JigMultiplayer_C` |
| Save system | EasyMultiSave plugin + `BFL_SaveGames` |

## Networking plumbing already compiled in

- `GameEngine.NetDriverDefinitions`: `GameNetDriver -> SteamSockets.SteamSocketsNetDriver`, fallback `IpNetDriver`.
  The dev configured Steam Sockets as the transport. Clients would connect with `open steam.<HostSteamID64>`.
- Plugins present: OnlineSubsystemSteam, SteamSockets, SteamCore (+Web), Iris, OodleNetworkHandlerComponent.
- `BP_PlayerCharacter_C`: 72 real net RPCs (Svr_*, MC_*, Client_*), bReplicates + bReplicateMovement true.
- `BP_PlayerController_C`: 6 RPCs (respawn requests, Client_Died).
- `BP_JigMultiplayer_C`: 61 RPCs. The inventory asset is MP-ready by design.
- bReplicates true on: player, zombies (BP_MasterAICharacter_C, BP_Zombie_C), Buildable_MASTER_C, BP_VehicleMaster_C, game state.
- bReplicates false on: BP_FirearmPickup_C (8 RPCs though), HUD_Game_C.
- Not yet known: which Blueprint variables are flagged Replicated. The probe's property-flag check did not work
  (Engine.Character also reported 0, so the check is wrong, not the game). Needs a different API or FModel.

## Toolchain installed

- UE4SS experimental (v3.0.1-1183-gcdbc0b66) in `SurrounDead\Binaries\Win64\` (`dwmapi.dll` + `ue4ss\`).
  Settings: console + GUI console on, DX11, hot reload on, engine version pinned 5.3.
  Verified: hooks in, all built-in Lua mods load, CheatManager enabled. Keys: `~` / F10 console, Ctrl+J object dump, Ctrl+H CXX headers.
- `mods/SDMP_AutoDump`: one-shot header/object dumper (disabled after use).
- `mods/SDMP_Probe`: writes `SDMP_probe.txt` with net flags for key classes. Copy of output in `dumps/`.
- `dumps/CXXHeaderDump`: 1756 headers, all game Blueprint classes. `dumps/UHTHeaderDump` (gitignored): native modules only.

## Phase 1 result (2026-10-25): listen server works

`open PersistentLevel?listen` issued from the main menu via `mods/SDMP_HostTest`:
- Before: world is already `/Game/Levels/PersistentLevel` at the main menu (menu lives inside the world), `World.NetDriver = nil`, PC has no pawn.
- After: `World.NetDriver = SteamSocketsNetDriver /Engine/Transient.SteamSocketsNetDriver_*`, game mode and game state re-created, no crash, stable for 2+ min.
- Still no pawn: the menu never spawns one. Player spawn happens in the New Game / Continue flow (`SD_GameInstance_C` spawn functions). Need to confirm that flow doesn't reload the level and drop `?listen`. `mods/SDMP_FlowTrace` hooks that flow.
- New Game flow (traced with `mods/SDMP_FlowTrace`, output in `dumps/SDMP_flow.txt`):
  `SD_GameInstance_C:Event_LoadLevel("LongdownValley")` -> `UnloadStreamLevel(MainMenu)` -> `LoadStreamLevel(LongdownValley)` ->
  ~7s later `BP_PlayerCharacter_C:ReceiveBeginPlay`, `BP_PlayerController_C:ReceivePossess(pawn)`, `SD_GameInstance_C:Survival_SpawnPlayer()`.
  No `OpenLevel` call anywhere, so the listen server survives entering the world. The host pawn is a normal server-side pawn.
  The world map is a streamed sub-level named `LongdownValley`; the main menu is the streamed sub-level `MainMenu`.
- Client spawn path for Phase 3: a joining player gets a PlayerController from the engine, but nothing calls the game's spawn
  logic for them. Plan: hook `GameModeBase:K2_PostLogin` and run the equivalent of `Survival_SpawnPlayer` for that controller,
  and make sure the client streams in `LongdownValley` (verify whether the engine replicates streaming state or we must call
  `LoadStreamLevel` client-side).
- Host SteamID64 (this PC): 76561198203054205. Client join command: `open steam.76561198203054205`.
- No game log is written (shipping build, logging compiled out). All observation is through UE4SS Lua.

## Phase 2 prep (2026-10-25)

- `mods/SDMP` is the real mod: console commands `sdmp_host`, `sdmp_join <SteamID64>`, `sdmp_join_ip`, `sdmp_status`,
  `sdmp_spawn`, `sdmp_spawntest`; keys F7 host, F6 status. Logs to `Win64\SDMP.log`.
  Host side: every 5s while hosting, any `BP_PlayerController_C` other than the local one that has no pawn gets a
  `BP_PlayerCharacter_C` spawned next to the host and possessed. Also hooks `K2_PostLogin` / `K2_OnLogout`.
  Client side: after joining, forces the `LongdownValley` streaming level loaded/visible and hides `MainMenu`.
- Dev switch: a file `Win64\SDMP_autohost.txt` makes the mod auto-host 35s after boot and run `sdmp_spawntest`
  once the host has a pawn. Delete the file for normal play.
- Verified: mod loads with no Lua errors, `sdmp_host` brings up the Steam Sockets driver (role=SERVER).
  Not yet verified: `World:SpawnActor` + `Possess` path (needs someone in-world; `sdmp_spawntest` covers it).
- Friend package: `package/SDMP-test-build.zip` (UE4SS + ConsoleEnabler + Keybinds + SDMP, GUI console off) plus `package/README.txt`.
  Rebuild after mod changes: see the Bash block in session history or re-copy `mods/SDMP` into `package/Win64/ue4ss/Mods/`.

## Loopback join test (2026-10-25): a second player joins and gets a body

Two instances of the game on one PC, launched directly (not via Steam) with `-nosteam -windowed`, so the engine
falls back to `IpNetDriver`. Env var `SDMP_DEV=host` / `SDMP_DEV=join:127.0.0.1` drives the mod (see main.lua).
- Host: `sdmp_host` -> IpNetDriver role=SERVER. Calling `SD_GameInstance_C:Event_LoadLevel("LongdownValley")` from Lua
  enters the world and spawns the host pawn with no menu clicking.
- Client: `open 127.0.0.1` -> role=CLIENT, `players=2`, host log shows `joined player without pawn` ->
  `SpawnActor` + `Possess` ok. Client sees its own pawn and the in-game HUD (`BP_Ingame_C`), so client RPCs work.
- The engine replicates streaming-level state: `LongdownValley` loads on the client by itself. The client's `MainMenu`
  sub-level stays loaded until the mod unloads it (fixed: identify levels via `GetLoadedLevel():GetOuter()`).
- Client view after a key press (`dumps/loopback_client_view.png`): third-person camera behind its own survivor, in-game HUD,
  menu gone. Survivor is the bare low-poly base mesh in an A-pose: no clothing/character-creator data and no animation on
  a mod-spawned pawn. The game's own spawn flow (`Survival_SpawnPlayer`) presumably applies those; Phase 4 item.
- Both show a "PRESS ANY KEY" overlay after load (normal game behaviour, grey screen until a key is pressed).
- Open issue: client reports 3 player pawns vs host's 2. Probably the game's own spawn logic also ran locally on the
  client (an un-replicated local body). Find which function spawns it (hook `Survival_SpawnPlayer` on the client) and suppress.
- Open issue: GetWorldAssetPackageName / PackageNameToLoad unusable from Lua here; ULevelStreaming objects are
  `LevelStreamingDynamic_0..4` (0 = MainMenu, 4 = LongdownValley).
- Steam Sockets path not yet exercised (needs two Steam accounts). Friend test uses `sdmp_join <SteamID64>`; if that fails,
  fallback is `sdmp_join_ip <host ip>` with both sides launched `-nosteam`... which loses Steam. Better fallback: leave Steam on
  and force the IP driver (TODO: find a way to pick IpNetDriver at runtime, e.g. `open 1.2.3.4` still uses GameNetDriver def).

## First real two-PC test over Steam (2026-10-25 17:18-17:31): connects, handshake stalls

Friend's client log (`sdmp_join: open steam.7656...`): SteamSocketsNetConnection objects are created, `World.NetDriver`
stays nil, role=standalone, no travel, no PlayerController events. Host log at 17:30: `connections=4` SteamSocketsNetConnection
on the SteamSocketsNetDriver but no `PostLogin` / `joined player`. So the Steam relay connection is established in both
directions at the Steam level, but the Unreal Hello/Challenge/Login/Welcome handshake never completes.
Suspects: SteamAuth packet handler component (`USteamAuthComponentModuleInterface` is compiled in), or a SteamSockets
quirk. Status lines now print `lastRecv` and `channels` per connection to tell which direction stalls.

Fallback built and verified: `setNetDriver()` rewrites `GameEngine.NetDriverDefinitions[GameNetDriver]` at runtime on
both the CDO and the live engine, so `open` uses IpNetDriver while Steam stays initialised. Loopback test with Steam
running: join + spawn + possess OK (`dumps/loopback_ip_with_steam_*.log`). Commands: `sdmp_host_ip`, `sdmp_join_ip <ip>`,
`sdmp_driver ip|steam`; keys Shift+F7 host-IP, F9 join host_ip from sdmp.ini. Needs UDP 7777 forwarded or a VPN.

## Radmin / IP attempt and the -nosteam finding (2026-10-25 18:57-19:07)

Friend joined the Radmin network; host pressed Shift+F7 (IP driver) 26s after launch via Steam: `driver=nil role=standalone`,
no listener. Friend's `open 26.122.57.40` saw `connections=0` (nothing to reach). Reproduced locally: launched **through
Steam**, `open PersistentLevel?listen` with the IP driver fails on all 4 retries, no UDP 7777 endpoint. Launched **directly
with `-nosteam`**, HOSTING OK first try, `0.0.0.0:7777` bound by the game. Conclusion: with the Steam online subsystem
active, IpNetDriver cannot bind plain UDP (Steam OSS takes over the default socket subsystem). All earlier successful IP
tests were direct launches. Decision: everyone sets Steam Launch Options `-nosteam`; host F7, joiner F9 over Radmin VPN.
`cmdHost` now verifies the driver after 8s and retries up to 4x, logging HOSTING OK / HOSTING FAILED.
Steam Sockets path is parked; see earlier section for the handshake stall.

## Steam launch vs direct launch (2026-10-25 19:12-19:20)

Even with Steam Launch Options `-nosteam` (confirmed on the command line), a Steam-launched process still brings up
SteamSocketsNetDriver on plain F7 and fails to bind IpNetDriver on forced IP (4 retries, no UDP 7777). Binary strings:
"SteamSockets: could not obtain a handle to SteamAPI!" — the SteamSockets plugin registers itself as the default socket
subsystem whenever SteamAPI initialises, which a Steam launch guarantees (SteamAppId env). `-nosteam` only disables the
OSS, not SteamShared/SteamSockets. Direct exe launch: SteamAPI has no appid, SteamSockets is skipped, IpNetDriver binds.
Decision: ship `Launch SurrounDead MP.bat` (direct launch with -nosteam) in the package; F7 now always forces the IP driver,
Ctrl+F7 / `sdmp_host_steam` keeps the Steam Sockets path for later.

## Distribution (2026-10-25)

Public repo: https://github.com/FullerK55/SurroundeadMP (branch master). `package/Win64/Launch SurrounDead MP.bat`
downloads the master zip from GitHub on every launch, copies `mods/SDMP/*` into `ue4ss\Mods\SDMP`, then starts the exe
with `-nosteam`. So: edit `mods/SDMP`, commit, push, and every friend gets it next launch. Rebuild
`package/SDMP-test-build.zip` only when UE4SS itself or the bat changes. `package/Win64/` is gitignored except the bat.

## First successful two-PC join and the fixes after it (2026-10-25 19:42-20:05)

- 19:42 over Radmin via the launcher: friend's controller logged in, host spawned a pawn, host crashed (access violation,
  UE4SS at the bottom of the stack). Cause: `LoopAsync`/`ExecuteWithDelay` callbacks run off the game thread; SpawnActor +
  Possess from there. Fix 0.1.1: every game-object call goes through `ExecuteInGameThread` (helper `gt()`).
- Second attempt: friend was in the world with the main menu still showing, clicked New Game, got a phantom body he
  couldn't control. Fix 0.1.2/0.1.3: on the client, remove `MenuWidget_C`/`LoadingScreenWidget_C` from the viewport and
  call `WidgetBlueprintLibrary:SetInputMode_GameOnly(pc, false)` once a pawn exists.
- GAME-FLOW trace (hooks must be registered ~12s after boot, BP classes aren't loaded earlier): on the client,
  `Event_LoadLevel` and then `Survival_SpawnPlayer` run by themselves when `LongdownValley` streams in, spawning a local
  non-networked `BP_PlayerCharacter_C`. Fix 0.1.4: on the client, destroy any `BP_PlayerCharacter_C` whose `GetLocalRole()`
  is Authority (3) (locally spawned); real pawns are AutonomousProxy/SimulatedProxy.
- Main-menu buttons (0.1.3): two instances of the game's `ButtonWidget_C` created with `WidgetBlueprintLibrary:Create`,
  added via `Quit:GetParent():AddChildToVerticalBox`. Clicks detected by hooking
  `ButtonWidget_C:BndEvt__ButtonWidget_Button_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature`
  and comparing the instance address. The menu widget only exists after the "press any key" screen; the injector polls.
  After hosting the menu is rebuilt; a status button "HOSTING OK - now click New or Load" is injected instead.

## Join feedback and a client crash (0.1.5, 2026-10-25 20:20-20:32)

- Join button now shows CONNECTING / HOST FOUND, LOADING / HOST NOT FOUND (15s). "Host found" = a NetConnection's
  `LastReceiveTime` advanced past the value first seen (it is stamped at creation, so a nonzero value alone means nothing).
  Verified: no host -> NOT FOUND at 15s; host -> found at ~1s, in world at ~5s.
- A client crashed (access violation, breadcrumb `/Game/Levels/MainMenu.MainMenu_C`) when the mod unloaded the MainMenu
  sub-level and removed `LoadingScreenWidget_C` in the same second the travel completed. Fix: never touch the loading
  screen; wait 4s after the pawn exists before removing the menu widget / setting input mode, 6s before any level
  streaming change. Two loopback rounds clean afterwards.
- Host log now prints PLAYER JOINED / PLAYER LEFT; the host's menu status entry shows the player count.

## Intermittent crash ~20s after launch, no join involved (0.1.6, 2026-10-25 20:37-20:53)

Host's game crashed 20s after a plain launch (access violation, call stack entirely inside UE4SS, right after
"[FCallbackGarbageCollector] Freed invalid callbacks!"). Reproduced 1 in 3 launches. Common factor: two
`ExecuteWithDelay(12000, gt(...))` callbacks (hook registration) firing just before UE4SS's callback GC; the
`ExecuteInGameThread` closure created inside a finished ExecuteWithDelay callback is the likely use-after-free.
Fix: ONE `LoopAsync(1000)` that runs a Lua scheduler (`after`/`every`/`cancel`) via a single `ExecuteInGameThread`
per tick; no ExecuteWithDelay anywhere. 5/5 cold launches clean, loopback clean. Rule for this mod: never use
ExecuteWithDelay, never nest ExecuteInGameThread inside another UE4SS async callback except the scheduler's.

## Death, respawn and "jumpy" movement (0.1.8, 2026-10-25 21:10-21:40)

- Tried using the game's own `Svr_RequestRespawn_Random` on the joined controller: it runs `Survival_Respawn` on the
  GameInstance, which is hard-wired to player controller 0, so it respawns/resets the HOST and the joiner gets nothing.
  That is also what happened when the friend clicked Respawn on his death screen ("I can't do anything"). Rejected.
- Host-side respawn: `spawnMissing` treats a pawn with `PlayerDead?` == true as missing; after 6s it UnPossesses the
  corpse and spawns a fresh body. Verified in loopback (pawn flagged dead -> new pawn possessed by the client 12s later).
- Client side: the death/respawn widgets (`RespawnScreen_C`, `BP_RespawnHUD_C`, `ScreenPermadeath_C`,
  `QuitWidgetRespawn_C`) are removed on sight so their buttons can't reset the host.
- Joiners only spawn once the host's body is settled (not falling, not at the origin); the dev entry path puts the
  host at the origin falling forever, so the dev host now teleports to 165450,49719,1600.
- Jitter hunt: movement component settings on the spawned pawn are identical to the host's (0 differences);
  no `Svr_SetActorLocation` spam; loopback walking shows host/client positions agreeing. ENetworkSmoothingMode is
  0 Disabled / 1 Linear / 2 Exponential and the game uses 2. Raised ListenServerNetworkSimulatedSmoothLocationTime
  0.04 -> 0.12 and MinNetUpdateFrequency 2 -> 30 on remote pawns; real-latency effect still to be confirmed with the friend.

## Plan

1. Host test, one machine: in the UE4SS console run `open PersistentLevel?listen` from the main menu and check the log for a
   listening SteamSocketsNetDriver. Compare with the game's own level load flow in `SD_GameInstance_C` so saves and player spawn still run.
2. Client test, second machine + second Steam account: `open steam.<HostSteamID64>`. Expect a pawn to spawn and move.
   If Steam Sockets fails, fall back to IP: temporarily swap the net driver definition and use a VPN (Tailscale/Radmin) or port forward 7777.
3. Fix what breaks, in order: player spawn/possess, inventory (already MP-aware), zombies (host-authoritative), loot/doors/building, save/load.
4. Packaging: a Lua mod for console/host/join UI plus, where blueprint logic must change, a patch pak built from a UE 5.3 dummy project.
