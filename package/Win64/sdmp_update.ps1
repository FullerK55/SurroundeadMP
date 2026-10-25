# SDMP updater: downloads the latest mod files from GitHub into ue4ss\Mods\SDMP.
# Called by "Launch SurrounDead MP.bat". Safe to run on its own. Never fails the launch.
param(
    [string]$Repo = "FullerK55/SurroundeadMP",
    [string]$Branch = "master"
)
$ErrorActionPreference = "Stop"
$gameDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$dst = Join-Path $gameDir "ue4ss\Mods\SDMP"
$tmp = Join-Path $env:TEMP "sdmp_update"
try {
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
    $ProgressPreference = "SilentlyContinue"
    if (Test-Path $tmp) { Remove-Item $tmp -Recurse -Force }
    New-Item -ItemType Directory $tmp | Out-Null
    $zip = Join-Path $tmp "repo.zip"
    Invoke-WebRequest -Uri "https://github.com/$Repo/archive/refs/heads/$Branch.zip" -OutFile $zip -TimeoutSec 30 -UseBasicParsing
    Expand-Archive $zip -DestinationPath $tmp -Force
    $src = Get-ChildItem $tmp -Directory | Where-Object { $_.Name -like "SurroundeadMP-*" } | Select-Object -First 1
    if (-not $src) { throw "repo folder not found in download" }
    $modSrc = Join-Path $src.FullName "mods\SDMP"
    if (-not (Test-Path (Join-Path $modSrc "Scripts\main.lua"))) { throw "mods\SDMP\Scripts\main.lua not in download" }

    New-Item -ItemType Directory -Force $dst | Out-Null
    Copy-Item (Join-Path $modSrc "*") $dst -Recurse -Force
    if (-not (Test-Path (Join-Path $dst "enabled.txt"))) { New-Item -ItemType File (Join-Path $dst "enabled.txt") | Out-Null }

    # also refresh this updater for next time (never the .bat: cmd reads a running batch file incrementally)
    $p = Join-Path $src.FullName "package\Win64\sdmp_update.ps1"
    if (Test-Path $p) { Copy-Item $p (Join-Path $gameDir "sdmp_update.ps1.new") -Force }

    $m = Select-String -Path (Join-Path $dst "Scripts\main.lua") -Pattern 'local VERSION = "([^"]+)"'
    $ver = if ($m) { $m.Matches[0].Groups[1].Value } else { "?" }
    Write-Host "[SDMP] Mod updated from GitHub ($Branch) to v$ver"
    Remove-Item $tmp -Recurse -Force
} catch {
    Write-Host "[SDMP] Update skipped: $($_.Exception.Message)"
    Write-Host "[SDMP] Launching with the mod version already installed."
}
