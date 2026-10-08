# Quirks of the C++ game

Found while reading the original source for the port. "Kept" means the Odin port reproduces it; "Fixed" means the port
deliberately differs. Ask the user before changing a "Kept" item.

## Rules (read in `GameData.cpp`, `Hunter.cpp`, `Creature.cpp`, `RoomGenerator.cpp`)

1. **Attack rolls exclude the maximum. Kept.** `Hunter::GetAttackStrength` rolls `rand() % (max - 1) + 1`, so 1 to max - 1.
   The status panel shows "1d{max}" but a normal-difficulty hunter with max 4 deals 1 to 3.
2. **Zombies strike from the cell the hunter left. Kept.** `MoveHunter` collects the four neighbours of the starting
   cell *before* moving and resolves attacks against those after the move. So a zombie beside the old cell hits you
   even though you walked away, a zombie beside only the new cell does not hit you until your next move, and bumping
   a wall next to a zombie still costs health.
3. **Armor soaking a hit still counts as a hit. Kept.** `Hunter::hit` is set whenever the amount is above 0, so the
   "hit hunter" sound plays even when armor absorbed everything. A trap plays its own sound and then the hit sound.
4. **Health upgrades heal. Kept.** Wounds are stored, not health; raising the maximum therefore adds the difference
   (25 to 30 on easy) to current health.
5. **Killing a creature: the original reads freed memory. Fixed.** `GameData::DamageCreature` calls
   `creatureCell->RemoveObject()`, which deletes the creature, and `~Creature` deletes its drop; it then calls
   `creatureCell->SetObject(drop)` with that dangling pointer. It evidently worked in practice (drops appear in the
   screenshots). The port implements the intent: the drop (if any) lies where the creature died.
6. **Pillars with four open sides become floor. Kept.** Terrain smoothing maps "no wall neighbours" (`flagMap[0]`) to
   `FLOOR`, and smoothing runs in place, column by column. A wall cell whose four neighbours are all floor turns into
   floor, which is why the original's levels have open halls. The port repeats the pass in the same order.
7. **Dead-end items are chosen in string order in the original. Not kept.** `nlohmann::json` iterates object keys as
   sorted strings ("0", "1", "10", "11", "2", ...), so the original placed item type 10 before 3. Only the order of
   random draws changes, never the result's distribution; the port goes in numeric order.
8. **Bombs and attacks work on any creature in the lit 3 by 3 area. Kept.** Bombs deal 10 to every lit creature,
   minibosses included (they have 20 health).
9. **Locks do not move the hunter. Kept.** Opening a lock removes it and leaves the hunter where he is (`stopsMovement`).
10. **The health bar of a creature with less than a tenth of its health left is empty. Kept.** The level is
    `(health - wounds) * 10 / health` rounded down, so a miniboss with 1 of 20 hit points shows no bar.
11. **`GenerateRandomNumberFromRange(0, 0)` divides by zero in the original** (placing dead-end items if there were
    fewer than 11 dead ends). Not reachable on 15 by 15 mazes in practice; the port reports a failed generation and
    tries again (every placement loop is capped, the original's loops were not).
12. **Randomness is different. By design.** The original used `rand()` seeded with the time; the port uses a seeded
    splitmix64, so levels cannot match the original's even for the same seed.

## Screens and shell (read in the renderers, command processors and `FortuneHunterApplication.cpp`)

13. **Music. Dropped.** The original's music never started when launched muted and unmuting did not start it. The port has no music at all (user decision), so the "MUX Volume" option is gone.
14. **The About screen says "(URL copied to clipboard!)".** The original copies the itch.io page URL when About is chosen.
    The port does the same through the page (browsers may refuse without a user gesture; a key press counts).
15. **The final score is added to the statistics each time a finished game is left by Back or Green.** A game can only be
    left that way once (it cannot be continued), so no double counting. The port keeps the logic, including re-reading the
    saved statistics before adding (two tabs add up).
16. **Quit.** The original's quit ends the process. A web page cannot, so Yes shows a goodbye message and stops the loop.
17. **Options menu starts on "Main Menu"** (`optionsState(OptionsState::BACK)`), and Left/Right on the mute and back items
    do nothing. Kept.
18. **Instruction labels overlap vertically on the third page** (16 pixel line spacing for 16 pixel glyphs); that is how
    `helppages.json` is laid out. Kept.
