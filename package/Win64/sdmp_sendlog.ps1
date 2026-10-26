# SDMP log sender (joiner side). Every 30s pushes the last 500 lines of SDMP.log to the host's receiver
# (host_ip from sdmp.ini, TCP 7778). Does nothing on the host itself. Exits when the game exits.
param([string]$TargetHost, [switch]$Once, [switch]$NoWait)
$gameDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$ini = Join-Path $gameDir "ue4ss\Mods\SDMP\Scripts\sdmp.ini"
if (-not $TargetHost) {
    if (-not (Test-Path $ini)) { exit 0 }
    $m = Select-String -Path $ini -Pattern '^\s*host_ip\s*=\s*(\S+)' | Select-Object -First 1
    if (-not $m) { exit 0 }
    $TargetHost = $m.Matches[0].Groups[1].Value
}
$myIps = @(Get-NetIPAddress -AddressFamily IPv4 -ErrorAction SilentlyContinue | ForEach-Object { $_.IPAddress })
if ($myIps -contains $TargetHost -and -not $Once) { exit 0 }   # we are the host
$log = Join-Path $gameDir "SDMP.log"
$name = $env:COMPUTERNAME
if (-not $NoWait) { Start-Sleep 20 }
while ($true) {
    try {
        if (Test-Path $log) {
            $tail = (Get-Content $log -Tail 500 -ErrorAction SilentlyContinue) -join "`n"
            $client = New-Object System.Net.Sockets.TcpClient
            $ar = $client.BeginConnect($TargetHost, 7778, $null, $null)
            if ($ar.AsyncWaitHandle.WaitOne(3000)) {
                $client.EndConnect($ar)
                $stream = $client.GetStream()
                $bytes = [System.Text.Encoding]::UTF8.GetBytes("LOG $name`n$tail")
                $stream.Write($bytes, 0, $bytes.Length); $stream.Flush()
                $client.Close()
            } else { $client.Close() }
        }
    } catch { }
    if ($Once) { break }
    Start-Sleep 30
    if (-not (Get-Process SurrounDead-Win64-Shipping -ErrorAction SilentlyContinue)) { break }
}
