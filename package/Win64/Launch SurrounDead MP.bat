@echo off
rem SDMP launcher: pulls the latest mod files from GitHub (sdmp_update.ps1), then starts the game
rem directly, NOT through Steam, so plain IP networking works. Steam can stay open.
cd /d "%~dp0"
if not exist "%~dp0SurrounDead-Win64-Shipping.exe" (
  echo.
  echo [SDMP] WRONG FOLDER. SurrounDead-Win64-Shipping.exe is not next to this file.
  echo [SDMP] This file is in:  %~dp0
  echo [SDMP] The game has TWO Win64 folders. The mod must go in the one under
  echo [SDMP]     SurrounDead\SurrounDead\Binaries\Win64\      ^(NOT  SurrounDead\Engine\Binaries\Win64\^)
  echo [SDMP] Move dwmapi.dll, the ue4ss folder, this .bat and sdmp_update.ps1 there, then run it again.
  echo.
  pause
  exit /b 1
)
echo [SDMP] Checking for mod updates...
if exist "%~dp0sdmp_update.ps1.new" move /y "%~dp0sdmp_update.ps1.new" "%~dp0sdmp_update.ps1" >nul
if exist "%~dp0sdmp_update.ps1" (
  powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0sdmp_update.ps1"
) else (
  echo [SDMP] sdmp_update.ps1 missing, skipping update.
)
if not exist "%~dp0ue4ss\Mods\SDMP\Scripts\main.lua" (
  echo [SDMP] ERROR: the mod is not installed and could not be downloaded. Install the zip first.
  pause
  exit /b 1
)
echo [SDMP] Starting SurrounDead...
start "" "%~dp0SurrounDead-Win64-Shipping.exe" -nosteam
