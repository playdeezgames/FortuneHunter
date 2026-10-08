#!/bin/bash
# Runs every test of the Odin port; exits non-zero on any failure. Usage: tools/test.sh
set -euo pipefail
cd "$(dirname "$0")/.."
mkdir -p build
fail=0
step() { echo; echo "== $1"; }

step "generated QR data is up to date and decodes (python)"
python3 tools/gen/gen_qr.py --check && echo "ok" || { echo "FAIL: qr_data.odin"; fail=1; }

step "native suite (odin test)"
odin test odin/tests -collection:fh=odin -o:speed -out:build/tests_native -define:ODIN_TEST_THREADS=1 2>&1 | tee build/native_tests.log | grep -E "FAIL|passed|failed|Finished|error" || true
grep -qE "All tests were successful|successful" build/native_tests.log || fail=1

step "web build (with the vet flags, so 32-bit and shadowing mistakes show)"
ODIN_FLAGS="-o:size" tools/build.sh >/dev/null && echo "ok" || { echo "FAIL: web does not build"; fail=1; }

step "wasm plays exactly like native (the same scripted game under node)"
ODIN_JS="$(odin root)/core/sys/wasm/js/odin.js" node tools/wasm_parity.js build/web build/parity_wasm.txt
if cmp -s build/parity_native.txt build/parity_wasm.txt; then echo "ok: $(cat build/parity_native.txt)"; else echo "FAIL: native and wasm digests differ"; cat build/parity_native.txt build/parity_wasm.txt; fail=1; fi

step "gamepad mapping (node)"
node tools/input_test.js && echo "ok" || { echo "FAIL: gamepad mapping"; fail=1; }

echo
if [ "$fail" = 0 ]; then echo "ALL TESTS PASSED"; else echo "SOME TESTS FAILED"; exit 1; fi
