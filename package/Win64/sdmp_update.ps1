# SDMP updater: downloads the latest mod files from GitHub into ue4ss\Mods\SDMP.
# Called by "Launch SurrounDead MP.bat". Safe to run on its own. Never fails the launch.
param(
    [string]$Repo = "FullerK55/SurroundeadMP",
    [string]$Branch = "master"
)
$ErrorActionPreference = "Stop"
$gameDir = Split-Path -Parent $MyInvocation.MyCommand.Path

# Desktop shortcut (pinnable to taskbar/Start because its target is cmd.exe, not the .bat)
try {
    $lnk = Join-Path ([Environment]::GetFolderPath("Desktop")) "SurrounDead MP.lnk"
    if (-not (Test-Path $lnk)) {
        $ws = New-Object -ComObject WScript.Shell
        $s = $ws.CreateShortcut($lnk)
        $s.TargetPath = "$env:WINDIR\System32\cmd.exe"
        $s.Arguments = "/c `"`"$gameDir\Launch SurrounDead MP.bat`"`""
        $s.WorkingDirectory = $gameDir
        $s.IconLocation = "$gameDir\SurrounDead-Win64-Shipping.exe,0"
        $s.Description = "SurrounDead multiplayer (updates the mod, then launches the game)"
        $s.Save()
        Write-Host "[SDMP] Created desktop shortcut 'SurrounDead MP' (right-click it to pin to taskbar or Start)"
    }
} catch { Write-Host "[SDMP] Could not create desktop shortcut: $($_.Exception.Message)" }
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

    # also refresh the helper scripts and stage a new updater / launcher for next time
    # (the running .bat is never overwritten directly: cmd reads a batch file incrementally; it swaps itself at its last line)
    foreach ($f in @("sdmp_logserver.ps1", "sdmp_sendlog.ps1", "sdmp_firewall.ps1")) {
        $p = Join-Path $src.FullName "package\Win64\$f"
        if (Test-Path $p) { Copy-Item $p (Join-Path $gameDir $f) -Force }
    }
    $p = Join-Path $src.FullName "package\Win64\sdmp_update.ps1"
    if (Test-Path $p) { Copy-Item $p (Join-Path $gameDir "sdmp_update.ps1.new") -Force }
    $p = Join-Path $src.FullName "package\Win64\Launch SurrounDead MP.bat"
    $cur = Join-Path $gameDir "Launch SurrounDead MP.bat"
    if ((Test-Path $p) -and (Test-Path $cur) -and ((Get-FileHash $p).Hash -ne (Get-FileHash $cur).Hash)) { Copy-Item $p "$cur.new" -Force }

    $m = Select-String -Path (Join-Path $dst "Scripts\main.lua") -Pattern 'local VERSION = "([^"]+)"'
    $ver = if ($m) { $m.Matches[0].Groups[1].Value } else { "?" }
    Write-Host "[SDMP] Mod updated from GitHub ($Branch) to v$ver"
    Remove-Item $tmp -Recurse -Force
} catch {
    Write-Host "[SDMP] Update skipped: $($_.Exception.Message)"
    Write-Host "[SDMP] Launching with the mod version already installed."
}

# Host only, one time: firewall rule so joiners' log senders can reach the receiver (TCP 7778, Radmin addresses only).
# "Host" = the host_ip in sdmp.ini is one of this PC's own addresses. Shows a UAC prompt once.
try {
    $ini = Join-Path $gameDir "ue4ss\Mods\SDMP\Scripts\sdmp.ini"
    $m = Select-String -Path $ini -Pattern '^\s*host_ip\s*=\s*(\S+)' -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($m) {
        $hostIp = $m.Matches[0].Groups[1].Value
        $mine = @(Get-NetIPAddress -AddressFamily IPv4 -ErrorAction SilentlyContinue | ForEach-Object { $_.IPAddress })
        if (($mine -contains $hostIp) -and -not (Get-NetFirewallRule -DisplayName "SDMP log receiver" -ErrorAction SilentlyContinue)) {
            Write-Host "[SDMP] You are the host: adding the firewall rule for joiner logs (one-time, needs admin: click Yes)"
            Start-Process powershell -Verb RunAs -ArgumentList "-NoProfile -ExecutionPolicy Bypass -File `"$gameDir\sdmp_firewall.ps1`"" -Wait
        }
    }
} catch { Write-Host "[SDMP] Firewall rule step skipped: $($_.Exception.Message)" }
