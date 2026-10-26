SurrounDead fan multiplayer (SDMP) - test build
================================================

INSTALL (2 steps)
1. In Steam: right-click SurrounDead > Manage > Browse local files.
   That opens the top folder, which contains TWO folders: "Engine" and "SurrounDead".
   Go INTO  SurrounDead  (NOT Engine), then  Binaries, then  Win64.
   You are in the right place when you see  SurrounDead-Win64-Shipping.exe  (about 116 MB).
   If you see files like tbb.dll but no SurrounDead-Win64-Shipping.exe, you are in the Engine one. Go back.
2. Drag everything from this zip's "Win64" folder into that folder. Overwrite if asked.
   You should now have  dwmapi.dll ,  a folder called  ue4ss , and  "Launch SurrounDead MP.bat"
   right next to SurrounDead-Win64-Shipping.exe.

LAUNCHING (important)
For multiplayer, do NOT start the game from Steam. Double-click  "Launch SurrounDead MP.bat"  in that
Win64 folder instead (right-click it > Send to > Desktop to make a shortcut). Steam can stay open.
Starting through Steam makes the game use Steam networking, which does not work with this mod yet.
The .bat also downloads the newest version of the mod from GitHub every time, so you never need a new zip
after the first install. If you are offline it just launches with whatever version you have.
A black text window opens alongside the game. That is the mod log. Leave it open.
If NO black window appears, the files are in the wrong folder. Re-read step 1.

RADMIN VPN (everyone)
1. Install Radmin VPN (free, no account): https://www.radmin-vpn.com
2. Joiners: Network > Join an existing network, enter the name and password the host gives you.
   The host must show a GREEN dot in your Radmin list before you try to join the game.

KEYS (click the game window first so it has focus)
  F6   print a status line to the black window
  F7   HOST (host only): at the main menu, wait 30 seconds after the menu appears, press F7 once.
       The black window must say  HOSTING OK  before you click New Game / Continue.
  F9   JOIN (joiners): at the main menu, press F9 once.
The host's Radmin address is already filled in at  ue4ss\Mods\SDMP\Scripts\sdmp.ini  (host_ip).

JOINING, STEP BY STEP
1. Wait until the host says HOSTING OK and that they are in the world.
2. Start the game with the .bat, stay on the MAIN MENU, click the game window once.
3. Press F9 once. Wait up to 30 seconds. If a "press any key" screen appears, press space.
4. Press F6: role=CLIENT and a pawn= line means you are in.

LOGS (automatic)
While you play, your mod log is sent to the host over Radmin every 30 seconds (nothing leaves the Radmin network).
Press F6 in game to add a status line to it. If that ever fails, F5 copies the log to your Desktop (SDMP-log.txt).
Host: the first launch asks once for admin rights to allow the log receiver from Radmin addresses only. Click Yes.
Joiner logs land in  SurrounDead\Binaries\Win64\joiner_logs\  on the host.

IF IT GOES WRONG
Send back  SurrounDead\Binaries\Win64\SDMP.log .

UNINSTALL
Delete  dwmapi.dll , the  ue4ss  folder and the .bat from the Win64 folder. The game is back to stock.
