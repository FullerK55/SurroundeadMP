# One-time, host only: allow the SDMP log receiver (TCP 7778) from Radmin VPN addresses (26.0.0.0/8) only.
# Runs elevated (UAC prompt). Safe to run again; it does nothing if the rule exists.
if (Get-NetFirewallRule -DisplayName "SDMP log receiver" -ErrorAction SilentlyContinue) { exit 0 }
New-NetFirewallRule -DisplayName "SDMP log receiver" -Direction Inbound -Protocol TCP -LocalPort 7778 -RemoteAddress 26.0.0.0/8 -Action Allow -Profile Any | Out-Null
