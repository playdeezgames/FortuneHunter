# Fortune Hunter of SPLORR!! is back, and it runs in yer browser

(Draft for the itch.io devlog. Written on October 8, 2026, the day of the rebuild, for posting when the browser build goes up on October 9. Written in the repo; the user posts it. Cut freely.)

Fortune Hunter is a little maze crawl I made on stream in early 2021: C++, SDL2, Visual Studio, Windows only. A dark labyrinth, a hundred zombies, locked doors, keys, diamonds, an exit you cannot use without an exit key. It never made it to a place where you could just click and play. Now it is.

## What it is

You are the hunter. The maze is 15 by 15 rooms drawn as 31 by 31 tiles, and you can only see what is near you. Walk into a zombie to hit it, walk into a lock to open it (you need a key, and the lock goes but you do not move, so you step again). Every dead end has a lock on it and a key somewhere else. The dead ends hold the diamonds, the exit key, the exit, and nine upgrades (attack, armor, health) each guarded by a miniboss. Bombs hurt everything in the light. Pick Easy, Normal or Hard, and see yer score at the end.

## What happened today

On October 8, 2026 I rebuilt it in Odin for the browser, in one sitting, working with Claude Code, an AI model. I want to be plain about the split. I decided what the game should be, what to keep and what to change, and I looked at it and played it. Claude wrote the Odin. It read the old C++ first, and we made a plan in seven pieces before anything was built: skeleton, drawing, rules, screens, sound, gamepad and touch, shipping.

Things I decided along the way:

- **Everything in the browser, one picture.** The game draws its own 640 by 480 frame and the page just shows it, scaled to fill the window with black bars where it has to.
- **Keyboard, gamepad and touch.** On a phone there are on-screen buttons, and you can drag a finger on the picture to walk.
- **No music.** The old game had a looping song. I dropped it for now, so the Options screen has Mute and the sound effects volume and nothing else.
- **The old game's odd rules, one at a time.** Reading the C++ turned up a pile of quirks, and I went through them and decided each. Some I kept on purpose: zombies hit you from the square you just left, the open halls where passages meet, bombs hitting the minibosses too. Some I changed: the attack roll now really goes up to the number the status panel shows (it used to top out one short), creatures always show a sliver of health bar while they live, and the Options screen opens on Mute. One I fixed because the original was broken: when you killed a creature carrying an item, the C++ read memory it had just freed. It happened to work.
- **The About screen shows a QR code** of my itch page instead of copying a link to yer clipboard. (If this ever goes on Steam, that has to go, because Steam does not want links to anywhere but Steam.)
- **I made the creatures' muddy dark outlines transparent**, so the hunter and the zombies are clean one-colour shapes.

## The honest part

Claude wrote nearly all of it, and some of it was wrong first.

- **The QR code was wrong the first time.** It drew a line through the three corner squares that has to stop short of them. Its own check passed, because the check made the same mistake. A test written straight from the QR spec caught it, and it is fixed. I have not scanned it with a real phone yet, and I will before it goes up.
- **I noticed zombies had stopped hitting me.** They had not. We had made a hit that yer armor soaks up completely silent, so with armor on, nothing told you it happened except a number dropping. We put the original sound back. A dedicated "armor took it" sound is still on the list, and I will have to make that sound myself.
- **The window scaling took a second go**, because the first version was not crisp enough at odd window sizes. It looks right to me now. If it looks soft on yer screen, tell me what screen and what size.

How it is checked: there are about 60 automated tests, including 150 generated mazes that must have the right number of everything, have every dead end locked, and be clearable with the keys that are in them, and one that plays a whole scripted game both in the normal program and in the WebAssembly build and requires the two to come out identical. The old game's data files are checked against the new code, so the tables cannot drift.

What has **not** been tried: a real gamepad, a real phone (touch was driven with simulated taps), Safari, and how the sounds sound out of the page. If something is off on one of those, that is why.

## Credits

The art and the sounds are mine, and so is the 2021 code. The 2026 Odin version was written with Claude Code (generative AI).

Controls: arrow keys to move, Space to choose or drop a bomb, Escape to go back. Gamepad: d-pad and A. Touch: the on-screen buttons, or drag on the picture.

Seeking fortune! And fame!
