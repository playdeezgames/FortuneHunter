#!/usr/bin/env python3
"""Generates odin/game/qr_data.odin: a QR code (version 3, error correction M, byte mode, best of the 8 masks) for the
About screen's link. No libraries; the encoder follows ISO/IEC 18004 and the result is checked by decoding it again
(`--check`, also run by tools/test.sh) before it is written. Usage: python3 tools/gen/gen_qr.py [--check]"""
import os, sys

URL = "https://thegrumpygamedev.itch.io/"
VERSION, SIZE, DATA_CW, ECC_CW = 3, 29, 44, 26  # version 3-M: one block of 44 data and 26 error correction codewords

# ---- Reed-Solomon over GF(256), polynomial 0x11D ----------------------------------------------------------
EXP, LOG = [0] * 512, [0] * 256
x = 1
for i in range(255):
    EXP[i] = x; LOG[x] = i
    x <<= 1
    if x & 0x100: x ^= 0x11D
for i in range(255, 512): EXP[i] = EXP[i - 255]

def gmul(a, b): return 0 if a == 0 or b == 0 else EXP[LOG[a] + LOG[b]]

def rs_generator(degree):
    poly = [1]
    for i in range(degree):
        nxt = [0] * (len(poly) + 1)
        for j, c in enumerate(poly):
            nxt[j] ^= c
            nxt[j + 1] ^= gmul(c, EXP[i])
        poly = nxt
    return poly  # highest degree first

def rs_remainder(data, degree):
    gen = rs_generator(degree)
    rem = list(data) + [0] * degree
    for i in range(len(data)):
        coef = rem[i]
        if coef:
            for j, g in enumerate(gen):
                rem[i + j] ^= gmul(g, coef)
    return rem[len(data):]

# ---- codewords -----------------------------------------------------------------------------------------------
def codewords(text):
    data = text.encode("ascii")
    bits = "0100" + format(len(data), "08b") + "".join(format(b, "08b") for b in data)
    assert len(bits) <= DATA_CW * 8, "text too long for version 3-M"
    bits += "0" * min(4, DATA_CW * 8 - len(bits))
    bits += "0" * (-len(bits) % 8)
    cw = [int(bits[i:i + 8], 2) for i in range(0, len(bits), 8)]
    pad = [0xEC, 0x11]
    while len(cw) < DATA_CW: cw.append(pad[(len(cw) - len(bits) // 8) % 2])
    return cw + rs_remainder(cw, ECC_CW)

# ---- matrix --------------------------------------------------------------------------------------------------
def function_modules():
    """Returns (dark, is_function): the fixed patterns of a version 3 symbol, and which modules they cover."""
    dark = [[False] * SIZE for _ in range(SIZE)]
    fn = [[False] * SIZE for _ in range(SIZE)]
    def put(x, y, v):
        if 0 <= x < SIZE and 0 <= y < SIZE: dark[y][x] = v; fn[y][x] = True
    for cx, cy in ((3, 3), (SIZE - 4, 3), (3, SIZE - 4)):  # finder patterns with their separators
        for dy in range(-4, 5):
            for dx in range(-4, 5):
                d = max(abs(dx), abs(dy))
                put(cx + dx, cy + dy, d not in (2, 4))
    for i in range(8, SIZE - 8):  # timing patterns run between the finder patterns only
        put(6, i, i % 2 == 0); put(i, 6, i % 2 == 0)
    for dy in range(-2, 3):  # the one alignment pattern of version 3, centred on (22, 22)
        for dx in range(-2, 3): put(22 + dx, 22 + dy, max(abs(dx), abs(dy)) != 1)
    put(8, SIZE - 8, True)  # the dark module
    for i in range(9): fn[8][i] = fn[i][8] = True  # format information areas (filled in later)
    for i in range(8): fn[8][SIZE - 1 - i] = fn[SIZE - 1 - i][8] = True
    return dark, fn

MASKS = [lambda x, y: (x + y) % 2 == 0, lambda x, y: y % 2 == 0, lambda x, y: x % 3 == 0, lambda x, y: (x + y) % 3 == 0,
         lambda x, y: (x // 3 + y // 2) % 2 == 0, lambda x, y: x * y % 2 + x * y % 3 == 0,
         lambda x, y: (x * y % 2 + x * y % 3) % 2 == 0, lambda x, y: ((x + y) % 2 + x * y % 3) % 2 == 0]

def data_positions(fn):
    """The data module positions in reading order: pairs of columns from the right, snaking up and down, skipping column 6."""
    out = []
    x, up = SIZE - 1, True
    while x > 0:
        if x == 6: x -= 1
        ys = range(SIZE - 1, -1, -1) if up else range(SIZE)
        for y in ys:
            for xx in (x, x - 1):
                if not fn[y][xx]: out.append((xx, y))
        x -= 2; up = not up
    return out

def format_bits(mask):
    data = 0b00 << 3 | mask  # error correction M is 00
    rem = data
    for _ in range(10): rem = (rem << 1) ^ ((rem >> 9) * 0x537)
    return (data << 10 | rem) ^ 0x5412

def draw_format(dark, mask):
    bits = format_bits(mask)
    b = lambda i: (bits >> i) & 1 == 1
    def set_(x, y, v): dark[y][x] = v
    for i in range(6): set_(8, i, b(i))
    set_(8, 7, b(6)); set_(8, 8, b(7)); set_(7, 8, b(8))
    for i in range(9, 15): set_(14 - i, 8, b(i))
    for i in range(8): set_(SIZE - 1 - i, 8, b(i))
    for i in range(8, 15): set_(8, SIZE - 15 + i, b(i))
    set_(8, SIZE - 8, True)

def penalty(m):
    score = 0
    for grid in (m, [list(r) for r in zip(*m)]):  # rows, then columns
        for line in grid:
            run = 1
            for i in range(1, SIZE):
                if line[i] == line[i - 1]: run += 1
                else:
                    if run >= 5: score += 3 + run - 5
                    run = 1
            if run >= 5: score += 3 + run - 5
            s = "".join("1" if v else "0" for v in line)
            for pat in ("10111010000", "00001011101"): score += 40 * sum(1 for i in range(SIZE - 10) if s[i:i + 11] == pat)
    for y in range(SIZE - 1):
        for x in range(SIZE - 1):
            if m[y][x] == m[y][x + 1] == m[y + 1][x] == m[y + 1][x + 1]: score += 3
    total = sum(v for row in m for v in row)
    k = (abs(total * 20 - SIZE * SIZE * 10) + SIZE * SIZE - 1) // (SIZE * SIZE) - 1  # steps of 5% away from half dark
    return score + 10 * max(k, 0)

def build(text):
    cw = codewords(text)
    bits = [(c >> (7 - i)) & 1 for c in cw for i in range(8)]
    base, fn = function_modules()
    positions = data_positions(fn)
    bits += [0] * (len(positions) - len(bits))  # version 3 has 7 remainder bits, which are zero before masking
    assert len(positions) == 567
    best = None
    for mask, rule in enumerate(MASKS):
        m = [row[:] for row in base]
        for (x, y), bit in zip(positions, bits): m[y][x] = bool(bit) != rule(x, y)
        draw_format(m, mask)
        p = penalty(m)
        if best is None or p < best[0]: best = (p, mask, m)
    return best[2], best[1]

# ---- decoding, to check ---------------------------------------------------------------------------------------
def decode(m):
    fmt = 0
    for i in range(6): fmt |= m[i][8] << i
    fmt |= m[7][8] << 6; fmt |= m[8][8] << 7; fmt |= m[8][7] << 8
    for i in range(9, 15): fmt |= m[8][14 - i] << i
    mask = next(k for k in range(8) if format_bits(k) == fmt)
    _, fn = function_modules()
    bits = [(m[y][x] != MASKS[mask](x, y)) for x, y in data_positions(fn)][:(DATA_CW + ECC_CW) * 8]
    cw = [int("".join("1" if b else "0" for b in bits[i:i + 8]), 2) for i in range(0, len(bits), 8)]
    data, ecc = cw[:DATA_CW], cw[DATA_CW:]
    assert rs_remainder(data, ECC_CW) == ecc, "error correction codewords do not match"
    stream = "".join(format(c, "08b") for c in data)
    assert stream[:4] == "0100", "not byte mode"
    n = int(stream[4:12], 2)
    return bytes(int(stream[12 + 8 * i:20 + 8 * i], 2) for i in range(n)).decode("ascii"), mask

def self_test():
    """Published test vectors: the error correction codewords of the version 1-M example in the spec's tutorials, and the
    format information bit strings for level M."""
    assert rs_remainder([32, 91, 11, 120, 209, 114, 220, 77, 67, 64, 236, 17, 236, 17, 236, 17], 10) == [196, 35, 39, 119, 235, 215, 231, 226, 93, 23]
    assert [format(format_bits(m), "015b") for m in range(3)] == ["101010000010010", "101000100100101", "101111001111100"]

def main():
    self_test()
    matrix, mask = build(URL)
    text, found = decode(matrix)
    assert text == URL and found == mask, (text, found, mask)
    rows = [sum(1 << x for x in range(SIZE) if matrix[y][x]) for y in range(SIZE)]
    out = ["package game", "", "// GENERATED by tools/gen/gen_qr.py; do not edit. A QR code (version 3, level M, mask %d) for" % mask,
           "//   " + URL, "// One u32 per row, top to bottom; bit x (from the least significant) is column x; 1 is a dark module.", "",
           "QR_SIZE :: %d" % SIZE, "QR_URL :: \"%s\"" % URL, "", "QR_ROWS :: [QR_SIZE]u32 {"]
    out += ["\t0x%08X," % r for r in rows] + ["}", ""]
    if "--check" in sys.argv:
        path = os.path.join(os.path.dirname(__file__), "..", "..", "odin", "game", "qr_data.odin")
        assert open(path).read() == "\n".join(out), "qr_data.odin is out of date: run tools/gen/gen_qr.py"
        print("qr_data.odin is up to date and decodes to", URL)
    else:
        with open(os.path.join(os.path.dirname(__file__), "..", "..", "odin", "game", "qr_data.odin"), "w") as f: f.write("\n".join(out))
        print("odin/game/qr_data.odin written, mask", mask)
        for y in range(SIZE): print("".join("##" if matrix[y][x] else "  " for x in range(SIZE)))

main()
