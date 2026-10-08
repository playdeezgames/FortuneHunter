#!/bin/bash
# Builds the web port into build/web (git-ignored). Usage: tools/build.sh   (ODIN_FLAGS="-o:size" for shipping)
set -euo pipefail
cd "$(dirname "$0")/.."
ASSETS="FortuneHunter/FortuneHunter/assets"
rm -rf build/web/assets
mkdir -p build/web
odin build odin/platform/web -target:js_wasm32 -out:build/web/platform.wasm -collection:fh=odin -vet-shadowing -vet-unused ${ODIN_FLAGS:-}
cp odin/platform/web/page/index.html odin/platform/web/page/platform.js odin/platform/web/page/storage.js odin/platform/web/page/audio.js odin/platform/web/page/input.js build/web/
cp "$(odin root)/core/sys/wasm/js/odin.js" build/web/odin.js
mkdir -p build/web/assets
cp -r "$ASSETS/images" build/web/assets/
mkdir -p build/web/assets/audio
cp -r "$ASSETS/audio/sfx" build/web/assets/audio/ # the music is not shipped
echo "web build: build/web (serve with tools/serve.sh)"
