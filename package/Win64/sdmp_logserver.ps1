# SDMP log receiver (host side). Listens on TCP 7778 (Radmin addresses only, via the firewall rule) and stores
# whatever a joiner's sender pushes into  Win64\joiner_logs\<name>.log . Exits when the game exits.
param([int]$Port = 7778, [switch]$KeepAlive)
$gameDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$outDir = Join-Path $gameDir "joiner_logs"
New-Item -ItemType Directory -Force $outDir | Out-Null
try { $listener = New-Object System.Net.Sockets.TcpListener([System.Net.IPAddress]::Any, $Port); $listener.Start() } catch { exit 1 }
$idle = 0
while ($true) {
    if ($listener.Pending()) {
        try {
            $client = $listener.AcceptTcpClient()
            $client.ReceiveTimeout = 5000
            $ip = $client.Client.RemoteEndPoint.Address.ToString()
            $stream = $client.GetStream()
            $reader = New-Object System.IO.StreamReader($stream, [System.Text.Encoding]::UTF8)
            $header = $reader.ReadLine()          # "LOG <name>"
            $body = $reader.ReadToEnd()           # sender shuts down its send side when done
            $name = "unknown"
            if ($header -match '^LOG\s+(.+)$') { $name = ($Matches[1] -replace '[^A-Za-z0-9_\-]', '_') }
            $file = Join-Path $outDir ("{0}_{1}.log" -f $name, ($ip -replace '[^0-9.]', '_'))
            [IO.File]::WriteAllText($file, $body, [System.Text.Encoding]::UTF8)
            # reply with the host's appearance file (asset paths) so the joiner can load the same meshes
            $app = Join-Path $gameDir "SDMP_appearance.txt"
            $reply = ""; if (Test-Path $app) { $reply = [IO.File]::ReadAllText($app) }
            $bytes = [System.Text.Encoding]::UTF8.GetBytes($reply)
            try { $stream.Write($bytes, 0, $bytes.Length); $stream.Flush() } catch { }
            $client.Close()
        } catch { }
    } else {
        Start-Sleep -Milliseconds 500
        $idle++
        if ($idle % 20 -eq 0 -and -not $KeepAlive) {
            if (-not (Get-Process SurrounDead-Win64-Shipping -ErrorAction SilentlyContinue)) { break }
        }
    }
}
$listener.Stop()
