#!/usr/bin/env python3
"""Draws the itch.io cover (630 by 500) from the game's own art: assets/cover.png. Needs Pillow."""
import os
from PIL import Image

ASSETS = "FortuneHunter/FortuneHunter/assets/images"
SPRITES = {  # x, y of 16 pixel cells in tiles.png
    "hunter": (0, 32), "zombie": (112, 32), "diamond": (96, 32), "key": (16, 32), "exitkey": (0, 48), "exit": (80, 32),
    "potion": (48, 64), "shield": (64, 64),
}

def text(font, s, scale):
    """Renders s with the ROM font (white on transparent, 16 pixel cells indexed by ASCII)."""
    img = Image.new("RGBA", (16 * len(s), 16), (0, 0, 0, 0))
    for i, ch in enumerate(s):
        c = ord(ch)
        img.paste(font.crop((c % 16 * 16, c // 16 * 16, c % 16 * 16 + 16, c // 16 * 16 + 16)), (i * 16, 0))
    return img.resize((img.width * scale, img.height * scale), Image.NEAREST)

def tint(img, rgb):
    r, g, b = rgb
    px = img.load()
    for y in range(img.height):
        for x in range(img.width):
            pr, pg, pb, pa = px[x, y]
            px[x, y] = (pr * r // 255, pg * g // 255, pb * b // 255, pa)
    return img

def main():
    os.chdir(os.path.join(os.path.dirname(__file__), ".."))
    bg = Image.open(f"{ASSETS}/backgrounds/mainmenu.png").convert("RGBA")
    font = Image.open(f"{ASSETS}/font.png").convert("RGBA")
    tiles = Image.open(f"{ASSETS}/tiles.png").convert("RGBA")
    cover = Image.new("RGBA", (630, 500), (0, 0, 0, 255))
    scaled = bg.resize((667, 500), Image.NEAREST)
    cover.paste(scaled.crop((18, 0, 648, 500)), (0, 0))
    for scale, y, s, rgb in ((2, 90, "Fortune Hunter", (85, 255, 85)), (2, 150, "of SPLORR!!", (255, 255, 85))):
        shadow = tint(text(font, s, scale), (0, 0, 0))
        main = tint(text(font, s, scale), rgb)
        x = (630 - main.width) // 2
        cover.alpha_composite(shadow, (x + 4, y + 4))
        cover.alpha_composite(main, (x, y))
    names = ["hunter", "key", "zombie", "diamond", "exitkey", "exit"]
    cell, gap = 16 * 5, 20
    x0 = (630 - (len(names) * cell + (len(names) - 1) * gap)) // 2
    floor = tiles.crop((0, 0, 16, 16))
    for i, n in enumerate(names):
        sx, sy = SPRITES[n]
        tile = floor.copy()
        tile.alpha_composite(tiles.crop((sx, sy, sx + 16, sy + 16)))
        cover.alpha_composite(tile.resize((cell, cell), Image.NEAREST), (x0 + i * (cell + gap), 330))
    os.makedirs("assets", exist_ok=True)
    cover.convert("RGB").save("assets/cover.png")
    print("assets/cover.png")

main()
