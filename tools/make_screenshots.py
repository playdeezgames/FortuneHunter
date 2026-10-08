#!/usr/bin/env python3
"""Writes assets/screenshots/*.png by playing the built wasm under node (run tools/test.sh or the native tests first so
build/parity_images exists, and tools/build.sh). Exact frames, no browser needed. Needs Pillow and node."""
import os, subprocess
from PIL import Image

os.chdir(os.path.join(os.path.dirname(__file__), ".."))
odin_js = subprocess.check_output(["odin", "root"], text=True).strip() + "/core/sys/wasm/js/odin.js"
walk = "green,right,right,down,down,left,up,up,up,right,right,right,down,down,down,down,left,left,up,up,right,right"
scenes = {
    "1-main-menu": (11, ""),
    "2-instructions": (11, "down,down,green"),
    "3-playing": (11, walk),
    "4-options": (11, "up,up,green"),
    "5-statistics": (11, "down,down,down,green"),
    "6-about": (11, "down,down,down,down,green"),
}
os.makedirs("assets/screenshots", exist_ok=True)
for name, (seed, keys) in scenes.items():
    raw = f"build/{name}.rgba"
    subprocess.check_call(["node", "tools/frame_dump.js", "build/web", str(seed), raw, keys], env={**os.environ, "ODIN_JS": odin_js})
    Image.frombytes("RGBA", (640, 480), open(raw, "rb").read()).convert("RGB").save(f"assets/screenshots/{name}.png")
    print(name)
