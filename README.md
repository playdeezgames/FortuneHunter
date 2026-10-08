# FortuneHunter
Seeking fortune! And fame!

A small maze crawler by TheGrumpyGameDev. Explore a dark labyrinth, fight zombies, open locks, find the exit key and the exit, and grab as many diamonds as you can.

The game was written in C++ with SDL2 in early 2021 and rewritten in Odin for the browser in October 2026.

## Layout

- `odin/` is the game: Odin, compiled to `js_wasm32`. `odin/game` is the portable core (rules, level generator, screens, software renderer, save format); `odin/platform/web` only shows its 640 by 480 frame, plays its sound effects, and passes keyboard, gamepad and touch input in.
- `FortuneHunter/` is the original C++ / SDL2 version (Visual Studio 2019). Its assets are what the Odin build uses, and some tests read its `config/` files.
- `docs/PORT_PLAN.md` and `docs/QUIRKS.md` record the port's decisions and the original's odd behaviour.

## Commands

```bash
tools/test.sh               # native tests, web build with vet flags, wasm-vs-native parity under node, gamepad mapping
tools/build.sh              # web build into build/web (ODIN_FLAGS="-o:size" for the shipping build)
tools/serve.sh              # http://localhost:8080 (PORT=... to change)
tools/ship.sh [--push]      # tests, optimized web build, zip; uploads with butler only with --push
```

Needs the Odin compiler (`dev-2026` nightly), Node.js for the parity test, Python 3 with Pillow for `tools/make_cover.py`.

Page URL options: `?seed=N` fixes the random numbers, `?log=1` prints every input, `?touch=1` shows the on-screen controls, `?keys=start,down,green` plays commands one per frame.

## Controls

Keyboard: arrows, Space (select / bomb), Enter (start), Esc (back), `,` and `.` (previous / next page). Gamepad: d-pad, A, Start, Back, bumpers. Touch: on-screen d-pad and buttons, or drag on the picture.

## Building the original C++ version in VS2019

* Dependencies
  * SDL2 https://www.libsdl.org/download-2.0.php
  * SDL2_mixer https://www.libsdl.org/projects/SDL_mixer/
  * SDL2_image https://www.libsdl.org/projects/SDL_image/
  * json.hpp https://github.com/nlohmann/json (its in the source, but provided here for reference)
* Project Settings To Check:
  * Configuration Properties/VC++ Directories/Include Directories
  * Configuration Properties/VC++ Directories/Library Directories
  * Configuration Properties/Debugging/Environment
