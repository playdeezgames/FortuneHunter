# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

"Fortune Hunter": a small turn-based maze crawler by TheGrumpyGameDev, written in C++17 with SDL2 in early 2021 (Visual Studio 2019 only; there is no Makefile or CMake, and no tests). The hunter explores a 15 by 15 cell maze (rendered as a 31 by 31 tile room), collects keys, opens locks, fights zombies, grabs diamonds and upgrades, finds the exit key, and leaves through the exit. Three difficulty levels, zombie bombs, statistics, final score, music and sfx. (The port has no music: user decision, see `docs/PORT_PLAN.md`.)

**Current goal: rewrite the game in Odin targeting `js_wasm32` (browser), the stack the author's other games already use, then ship it.** This is the first game ported from C++ (the others were VB.NET or Lua). The plan comes first, then the port. The C++ source stays as the reference until the port ships.

Background lives in the Obsidian vault at `/home/yermom/git/bok-of-splorr/splorr/`. Read `Tech/Odin wasm recipe.md` (the build, frame loop, input, canvas shim, and the Murder Hobo / Kordanor's Cabal "one core, shared framebuffer" split), `Gotchas.md` and `Tech/Shipping to itch.io.md` before writing Odin. Finished ports to copy structure from: `/home/yermom/git/murder-hobo-of-splorr` (has a good `CLAUDE.md`, `tools/test.sh`, `tools/build.sh`, `tools/ship.sh`, native SDL2 client, wasm parity test), `KordanorsCabal`, `shark-attackers-of-splorr`, `robokitteh-of-splorr`.

The decisions for the port (software framebuffer, web only, JS-decoded PNGs, Web Audio shim, compiled-in Odin tables, faithful with documented quirks, keyboard + gamepad + touch) and the milestones are in `docs/PORT_PLAN.md`. Follow it.

## Standing rules (from the author's other repos)

- **A possible Steam version must not link to anything except its own Steam page**: the About screen's itch.io URL and QR code would have to go (`docs/QUIRKS.md` item 14).

- Never run `butler push`, `tools/ship.sh --push`, `shippit.sh --push` or `git push` unless the user says so in chat. Commit only when asked.
- Do not `pkill -f` patterns that also match your own command line (it kills the shell); and do not start two `tools/test.sh` runs at once (they share `build/`).
- Do not "fix" deliberate design; if behaviour of the C++ game looks odd, record it (a `docs/QUIRKS.md`) and ask before changing it.

## Commands (the Odin port)

```bash
tools/test.sh    # about 2 minutes: native tests (odin test, -o:speed, one thread), the web build with vet flags (-o:size), wasm-vs-native parity under node, gamepad mapping test
tools/build.sh   # web build into build/web (git-ignored); ODIN_FLAGS="-o:size" for shipping
tools/ship.sh    # tests, -o:size build, zip in build/; uploads to itch.io ONLY with --push (never run it unless the user says so)
tools/serve.sh   # serves build/web on http://localhost:8080 (PORT=... to change; check the port is free)
odin test odin/tests -collection:fh=odin -o:speed -out:build/t -define:ODIN_TEST_THREADS=1 -define:ODIN_TEST_NAMES=tests.<name>   # one test
```

Odin is `dev-2026-07-nightly` at `/home/yermom/ODIN/odin`. Layout and status of each milestone: `docs/PORT_PLAN.md`; C++ quirks and what the port does about them: `docs/QUIRKS.md`. Some tests (`odin/tests/fidelity_test.odin`, the image loading tests) read the C++ game's `config/` and `assets/` from `FortuneHunter/FortuneHunter/`; they stop working if that folder moves.

## Building the original C++ game (reference only)

Windows, VS2019, open `FortuneHunter/FortuneHunter.sln`. Needs SDL2, SDL2_mixer (OGG), SDL2_image and `json.hpp` (vendored). Include/library directories and the debugging working directory (must be the folder holding `assets/` and `config/`) are set in the project settings; see `README.md`. It is not buildable on this Linux machine as-is.

## Layout

All source is in `FortuneHunter/FortuneHunter/` (the solution folder contains a project folder of the same name). Also: `FortuneHunter/TODO` (finished task archive that records design decisions and difficulty tables), `Documentation*.pdf` / `Documentation.rtf` (the manual text, which the instructions screens reproduce), `pdns/` (Paint.NET sources of the backgrounds), `FortuneHunter/screenshots/`.

Data the port needs, all in `FortuneHunter/FortuneHunter/`: `assets/images/` (`tiles.png`, `font.png`, `romfont8x8.png`, eight 640x480 `backgrounds/*.png`, `icon.png`), `assets/audio/sfx/*.wav` (17 effects), `assets/audio/mux/` (one OGG, Komiku "You can't beat the machine", unused by the port), and `config/*.json`.

## Architecture of the C++ game

Fixed window 640x480. Almost everything is wired in the `FortuneHunterApplication` constructor and `Start()`; read `FortuneHunterApplication.cpp` first.

- **`tggd::common` framework classes** (templates and base classes, generic): `Application` (SDL window and loop), `Renderer` / `RenderManager`, `CommandProcessor` / `CommandProcessorManager`, `EventHandler`, `FinishManager` (ordered cleanup registry; managers register themselves), `Room<TTerrain, TObjectData, TCellFlags>` (grid of `RoomCell`s holding terrain, a stack of `RoomCellObject`s and flag bits), `BaseDescriptor` / `BaseDescriptorManager`, texture / sprite / sound / color managers, `SpriteFont` (8x8 ROM font drawn from a sprite sheet with palette colors), `Label`.
- **UI state machine**: `UIState` (MAIN_MENU, IN_PLAY, OPTIONS, ABOUT, INSTRUCTIONS, CONFIRM_QUIT, FINAL_SCORE, STATISTICS). Each state has a `*Renderer` and a `*CommandProcessor`; the managers dispatch to whichever matches the current `UIState`. `FortuneHunterEventHandler` maps keyboard and gamepad (`ControllerManager`) input to a small `Command` enum (arrows, four colour buttons, next/previous/back/start). Screens render a background image plus text on top.
- **Game rules live in `GameData`** (hunter movement, attack resolution, bombs, item pickup, lighting/exploring, difficulty, score) plus `Hunter`, `Creature`, `Item` (objects placed in the room). `RoomGenerator` builds a level: `Maze` generates a perfect maze, `LoopifyMaze` knocks out walls (`LOOPIFICATIONS = 48`), `ScaffoldMaze` converts the maze to terrain, then locks/keys, dead-end items, creatures and loose items are placed from descriptor counts. Cell flags (lit, explored, ...) drive fog of war in `RoomPanelRenderer`.
- **Data-driven content**: creature, item and hunter descriptors, sprite tables, colors, sfx/mux, textures and help pages are JSON in `config/`, loaded by `*DescriptorManager`s and referenced by numeric enum values (`ObjectType`, `TerrainType`, `ItemType`; enum numbers in the JSON must match the enums in the `.h` files). Spawn rules (`numberAppearing`, `deadEndAppearing`, `canSpawnOnTerrain`, `canSpawnOnObject`) are in the descriptors, not the code. Difficulty tables (health, weapon, armor, scores, bombs per easy/normal/hard) are in the `TODO` archive and the hunter descriptors.
- **Persistence**: `Options` (difficulty, mute, sfx/mux volume) and `Statistics` (games played/won/lost, high score, total score) are read from and written to `config/options.json` and `config/statistics.json` at runtime. In the port these become `localStorage` keys, namespaced (every itch.io HTML5 game shares one `localStorage` origin).
- **Audio**: SDL2_mixer; music loops, sfx on a free channel, volumes 0..128. The port plays only the sfx.

## Porting notes

- Likely Odin shape (per the vault recipe): a platform-free `game` package (rules, generator, screens state machine, software rasteriser or a tile/text grid over the 640x480 or tile-based canvas), a `#+build js` web platform with a 2D-canvas page (no WebGL; see Gotchas), and optionally a native SDL2 client, with native `odin test` for the rules and generator (`#+build !js` on test files, `-define:ODIN_TEST_THREADS=1`).
- Replace runtime JSON loading of content with Odin data/tables compiled in (or validate rigorously: `core:encoding/json` silently accepts unknown enum names); `core:os` panics on `js_wasm32`.
- Time and randomness should be arguments to the core, not read inside, so tests can force outcomes. Cap every random-placement retry loop. Do not use `int` for values that may exceed 32 bits (wasm `int` is 32-bit).
- Assets must be copied beside `index.html` (tiles, fonts, backgrounds as images; sfx via Web Audio / `<audio>` in the JS shim, since Odin cannot play audio itself). Browsers need a user gesture before audio starts.
- Odin is `dev-2026-07-nightly` at `/home/yermom/ODIN/odin`.
