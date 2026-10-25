-- SDMP_AutoDump: one-shot dumper used during research.
-- Waits for the main menu to settle, then writes CXX headers, UHT headers,
-- and a full UObject dump next to UE4SS. Disable in mods.txt when not needed.
local DELAY_MS = 45000

print("[SDMP_AutoDump] armed, dumping in " .. (DELAY_MS / 1000) .. "s\n")

ExecuteWithDelay(DELAY_MS, function()
    print("[SDMP_AutoDump] GenerateSDK (CXX headers)...\n")
    GenerateSDK()
    print("[SDMP_AutoDump] DumpAllObjects...\n")
    DumpAllObjects()
    print("[SDMP_AutoDump] GenerateUHTCompatibleHeaders...\n")
    GenerateUHTCompatibleHeaders()
    print("[SDMP_AutoDump] DONE\n")
end)
