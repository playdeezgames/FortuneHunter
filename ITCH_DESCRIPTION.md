# Itch.io page text

## Paste this as the page description

Seeking fortune! And fame!

As the FORTUNE HUNTER, your goal is to acquire as many DIAMONDS from the maze as you can. Beware, though, because the labyrinth is filled with ZOMBIES, who will strike at you as you move near them. To attack a ZOMBIE, simply move into them. The DIAMONDS are behind locked DOORS that you will need KEYS to open. To open a LOCK, simply move into it. Finally, to exit the dungeon, you will need an EXIT KEY which will allow you to leave via the EXIT.

There are a lot of ZOMBIES, but despair not! There are numerous POTIONS and SHIELDS to help you, as well as ATTACK, ARMOR and HEALTH upgrades guarded by minibosses. Use yer BOMBS sparingly: they hurt every zombie in the light.

**Controls:** arrow keys to move, Space to select a menu item or drop a bomb, Escape to go back. A gamepad works too (d-pad and A), and on a phone or tablet there are on-screen buttons and you can drag on the picture to walk.

**Difficulty:** pick Easy, Normal or Hard on the main menu before you start. Harder means fewer hit points and bombs, and bigger scores.

**Saving:** yer options, difficulty and statistics are kept in yer browser. A game in progress is not saved: close the tab and it is gone.

Originally written in C++ in 2021, rebuilt in Odin for the browser in 2026.

## Notes (not for the page)

- Create the page first, then check the slug: `tools/ship.sh` pushes to `thegrumpygamedev/fortune-hunter-of-splorr:html`, which is a guess. Change `TARGET` in `tools/ship.sh` if the page is called something else.
- On the page's Edit game screen: set "Kind of project" to HTML, tick "This file will be played in the browser" on the html upload, and make the embed 640 by 480 (or larger, it scales).
- The cover is `assets/cover.png` (630 by 500, drawn by `tools/make_cover.py`); screenshots are in `assets/screenshots/`.
- Credits to fill in by hand: where the 8 by 8 font, the sound effects and the tile art came from. The repo does not say. (The music was dropped from the port.)
- Fill in the page's generative AI disclosure if you want to mention that the Odin port was written with Claude Code.
