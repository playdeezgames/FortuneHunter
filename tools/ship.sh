#!/bin/bash
# Prepares the itch.io build: tests, an optimized web build, a zip. Pushes ONLY with --push. Never commits, never deletes
# anything. Usage: tools/ship.sh [--push]
set -euo pipefail
cd "$(dirname "$0")/.."
# The itch.io page's slug is a guess until the user creates the page: change it here if the page is called something else.
TARGET="thegrumpygamedev/fortune-hunter-of-splorr:html"
ZIP="build/fortune-hunter-html5.zip"

tools/test.sh
ODIN_FLAGS="-o:size" tools/build.sh
rm -f "$ZIP"
(cd build/web && zip -q -9 -r "../fortune-hunter-html5.zip" .)
echo "zip: $ZIP ($(du -h "$ZIP" | cut -f1)); wasm $(du -h build/web/platform.wasm | cut -f1)"
unzip -l "$ZIP" | tail -5

if [ "${1:-}" = "--push" ]; then
	if [ -n "$(git status --porcelain)" ]; then echo "note: the working tree has uncommitted changes; what is pushed is the working tree, not a commit"; fi
	butler push "$ZIP" "$TARGET"
	echo "pushed to $TARGET. It goes live after itch.io processes it; check: butler status $TARGET"
else
	echo "not pushed (run tools/ship.sh --push when you want it live; the target is $TARGET)"
fi
