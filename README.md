# Magshess

Denis Liubarsky and Marom Shpak present: **Magshess**!

## Building

### Windows
Everything should work out of the box, just open the solution and press build.

Make sure that you are indeed using VS2022 or have MSVC v143 build tools
installed.

If you are getting DLL not found issues, make sure you are building in debug
mode, and that the DLLs are indeed present in the same directory as the exe.

If you don't have the DLLs you can acquire them [here](https://github.com/brainboxdotcc/DPP/releases/download/v10.0.29/libdpp-10.0.29-win64-debug-vs2022.zip).

### Linux

After installing [D++](https://dpp.dev), compile all the cpp files with `g++ -lm -ldpp -D DPP` and run

## Running
The project is designed to run from a terminal/cmd or with specified arguments
via VisualStudio.

To run in MagshimimUI mode, specify the `--magshimim` flag, and start the
Magshimim UI.
*Note: Castling although works in MagshimimUI mode, will cause rook's to be out
of sync with it's actual position. That's not a problem in discord mode.*

To run is Discord mode, specify the `--discord` flag, and enter the discord bot
token to use for the chess bot. You can also specify the token inside an ENV
VAR `BOT_TOKEN`.

## If you face any problems
Please open an issue on GitHub explaining what went wrong

## Live demo
There's a live instance of the bot currently running, invite it using
[this link](https://discord.com/api/oauth2/authorize?client_id=1190552081329827891&permissions=2147483648&scope=bot).
