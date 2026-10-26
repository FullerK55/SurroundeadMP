@echo off
rem SDMP launcher: pulls the latest mod files from GitHub (sdmp_update.ps1), then starts the game
rem directly, NOT through Steam, so plain IP networking works. Steam can stay open.
rem Also starts two silent helpers: the log receiver (host) and the log sender (joiners).
rem NOTE: no parenthesized blocks in this file; the install path may contain "(x86)".
cd /d "%~dp0"
if not exist "%~dp0SurrounDead-Win64-Shipping.exe" goto wrongfolder

echo [SDMP] Checking for mod updates...
if exist "%~dp0sdmp_update.ps1.new" move /y "%~dp0sdmp_update.ps1.new" "%~dp0sdmp_update.ps1" >nul
if not exist "%~dp0sdmp_update.ps1" goto noupdater
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0sdmp_update.ps1"
goto checkmod

:noupdater
echo [SDMP] sdmp_update.ps1 missing, skipping update.

:checkmod
if not exist "%~dp0ue4ss\Mods\SDMP\Scripts\main.lua" goto nomod
echo [SDMP] Starting SurrounDead...
start "" "%~dp0SurrounDead-Win64-Shipping.exe" -nosteam
rem helpers (hidden). The receiver only matters on the host; the sender only acts on joiners.
if exist "%~dp0sdmp_logserver.ps1" start "" /min powershell -NoProfile -ExecutionPolicy Bypass -WindowStyle Hidden -File "%~dp0sdmp_logserver.ps1"
if exist "%~dp0sdmp_sendlog.ps1" start "" /min powershell -NoProfile -ExecutionPolicy Bypass -WindowStyle Hidden -File "%~dp0sdmp_sendlog.ps1"
rem self-update must be the LAST line: cmd has already read it, so replacing the file now is safe
if exist "%~dp0Launch SurrounDead MP.bat.new" move /y "%~dp0Launch SurrounDead MP.bat.new" "%~dp0Launch SurrounDead MP.bat" >nul & exit /b 0

:nomod
echo [SDMP] ERROR: the mod is not installed and could not be downloaded. Install the zip first.
pause
exit /b 1

:wrongfolder
echo.
echo [SDMP] WRONG FOLDER. SurrounDead-Win64-Shipping.exe is not next to this file.
echo [SDMP] This file is in:  %~dp0
echo [SDMP] The game has TWO Win64 folders. The mod must go in the one under
echo [SDMP]     SurrounDead\SurrounDead\Binaries\Win64\      and NOT under  SurrounDead\Engine\Binaries\Win64\
echo [SDMP] Move dwmapi.dll, the ue4ss folder, this .bat and sdmp_update.ps1 there, then run it again.
echo.
pause
exit /b 1
