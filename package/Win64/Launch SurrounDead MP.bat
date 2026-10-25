@echo off
setlocal
rem SDMP launcher: pulls the latest mod files from GitHub, then starts the game directly (not through Steam).
rem Edit REPO if the project moves. No git install needed; uses PowerShell to download the zip.
set "REPO=FullerK55/SurroundeadMP"
set "BRANCH=master"
cd /d "%~dp0"

echo [SDMP] Checking for mod updates from %REPO% (%BRANCH%)...
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
  "$ErrorActionPreference='Stop';" ^
  "try {" ^
  "  $tmp = Join-Path $env:TEMP 'sdmp_update'; if (Test-Path $tmp) { Remove-Item $tmp -Recurse -Force };" ^
  "  New-Item -ItemType Directory $tmp | Out-Null;" ^
  "  $zip = Join-Path $tmp 'repo.zip';" ^
  "  Invoke-WebRequest -Uri 'https://github.com/%REPO%/archive/refs/heads/%BRANCH%.zip' -OutFile $zip -TimeoutSec 30;" ^
  "  Expand-Archive $zip -DestinationPath $tmp -Force;" ^
  "  $src = Get-ChildItem $tmp -Directory | Where-Object { $_.Name -like 'SurroundeadMP-*' } | Select-Object -First 1;" ^
  "  $modSrc = Join-Path $src.FullName 'mods\SDMP';" ^
  "  if (-not (Test-Path $modSrc)) { throw 'mods\SDMP not found in download' };" ^
  "  $dst = Join-Path (Get-Location) 'ue4ss\Mods\SDMP';" ^
  "  New-Item -ItemType Directory -Force $dst | Out-Null;" ^
  "  Copy-Item (Join-Path $modSrc '*') $dst -Recurse -Force;" ^
  "  if (-not (Test-Path (Join-Path $dst 'enabled.txt'))) { New-Item -ItemType File (Join-Path $dst 'enabled.txt') | Out-Null };" ^
  "  $ver = (Select-String -Path (Join-Path $dst 'Scripts\main.lua') -Pattern 'local VERSION = \"([^\"]+)\"').Matches[0].Groups[1].Value;" ^
  "  Write-Host ('[SDMP] Mod updated to v' + $ver);" ^
  "  Remove-Item $tmp -Recurse -Force" ^
  "} catch { Write-Host ('[SDMP] Update skipped: ' + $_.Exception.Message); Write-Host '[SDMP] Launching with the mod version already installed.' }"

if not exist "ue4ss\Mods\SDMP\Scripts\main.lua" (
  echo [SDMP] ERROR: the mod is not installed and could not be downloaded. Install the zip first.
  pause
  exit /b 1
)
echo [SDMP] Starting SurrounDead...
start "" "%~dp0SurrounDead-Win64-Shipping.exe" -nosteam
endlocal
