package game

// The instruction pages of config/helppages.json. Labels are drawn in order, so the brown highlight labels come after
// the white text they sit on. A label with a drop shadow draws its shadow colour first, offset by (x, y).

Help_Label :: struct {
	x, y:        int,
	text:        string,
	color:       Color,
	shadow:      bool,
	shadow_x, shadow_y: int,
	shadow_color: Color,
}

Help_Page :: struct {
	labels: []Help_Label,
}

// Pages go first, second, third and wrap around (every page's next and previous in the JSON follow that order).
HELP_PAGE_COUNT :: 3

help_labels_0 := [?]Help_Label {
	{x = 224, y = 0, text = "==THE GOAL==", color = .Light_Green, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 32, text = "As the FORTUNE HUNTER, your goal is to", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 56, text = "acquire as many DIAMONDS from the maze", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 80, text = "as you can. Beware, though, because the", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 104, text = "labyrinth is filled with ZOMBIES, who", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 128, text = "will strike at you as you move near", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 152, text = "them. To attack a ZOMBIE, simply move", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 176, text = "into them. The DIAMONDS are behind", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 200, text = "locked DOORS that you will need KEYS", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 224, text = "to open. To open a LOCK, simply move", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 248, text = "into it. Finally, to exit the dungeon,", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 272, text = "you will need an EXIT KEY which will", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 296, text = "allow you to leave via the EXIT. There", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 320, text = "are a lot of ZOMBIES, but despair not!", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 344, text = "There are numerous POTIONS and SHIELDS", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 368, text = "to help you, as well as ATTACK,", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 392, text = "ARMOR, and HEALTH UPGRADES.", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 416, text = "Best of luck, FORTUNE HUNTER!", color = .White, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 112, y = 32, text = "FORTUNE HUNTER", color = .Brown},
	{x = 256, y = 56, text = "DIAMONDS", color = .Brown},
	{x = 400, y = 104, text = "ZOMBIES", color = .Brown},
	{x = 288, y = 152, text = "ZOMBIE", color = .Brown},
	{x = 240, y = 176, text = "DIAMONDS", color = .Brown},
	{x = 112, y = 200, text = "DOORS                    KEYS", color = .Brown},
	{x = 304, y = 224, text = "LOCK", color = .Brown},
	{x = 272, y = 272, text = "EXIT KEY", color = .Brown},
	{x = 432, y = 296, text = "EXIT", color = .Brown},
	{x = 208, y = 320, text = "ZOMBIES", color = .Brown},
	{x = 304, y = 344, text = "POTIONS     SHIELDS", color = .Brown},
	{x = 384, y = 368, text = "ATTACK", color = .Brown},
	{x = 0, y = 392, text = "ARMOR      HEALTH UPGRADES.", color = .Brown},
	{x = 224, y = 416, text = "FORTUNE HUNTER", color = .Brown},
}

help_labels_1 := [?]Help_Label {
	{x = 224, y = 0, text = "==CONTROLS==", color = .Green, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 32, text = "<KEYBOARD>/(GamePad)", color = .Cyan, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 64, text = "<ARROWS>/(D-Pad)", color = .Cyan, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 192, y = 80, text = "Navigate/move", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 112, text = "<ESC>/(Back)", color = .Cyan, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 192, y = 128, text = "Go back", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 160, text = "<SPACE>/<ENTER>/(A)/(Start)", color = .Cyan, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 192, y = 176, text = "Select menu item/Use Bomb", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
}

help_labels_2 := [?]Help_Label {
	{x = 176, y = 0, text = "==HINTS AND TIPS==", color = .Green, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 32, text = "1). Items in this game are immediately", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 48, text = "used upon collecting them, which means", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 64, text = "that when you pick up a POTION, you ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 384, y = 64, text = "POTION", color = .Brown},
	{x = 0, y = 80, text = "immediately drink it, and when you pick ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 96, text = "up a SHIELD, your ARMOR instantly goes ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 80, y = 96, text = "SHIELD       ARMOR", color = .Brown},
	{x = 0, y = 112, text = "up. Since a POTION gives you a parti-", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 192, y = 112, text = "POTION", color = .Brown},
	{x = 0, y = 128, text = "cular amount of HEALTH back, and because ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 256, y = 128, text = "HEALTH", color = .Brown},
	{x = 0, y = 144, text = "your ARMOR statistic has a maximum based ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 80, y = 144, text = "ARMOR", color = .Brown},
	{x = 0, y = 160, text = "on your current upgrade level, you may ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 176, text = "not always receive the full benefit of ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 192, text = "the POTION or SHIELD.", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 64, y = 192, text = "POTION    SHIELD.", color = .Brown},
	{x = 0, y = 224, text = "2). After each move you make, you will ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 240, text = "be struck by every ZOMBIE that was adj-", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 304, y = 240, text = "ZOMBIE", color = .Brown},
	{x = 0, y = 256, text = "acent to you that lives after your move ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 272, text = "is complete. Attempt to face ZOMBIES one ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 464, y = 272, text = "ZOMBIES", color = .Brown},
	{x = 0, y = 288, text = "at a time to minimize ARMOR and HEALTH ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 352, y = 288, text = "ARMOR     HEALTH ", color = .Brown},
	{x = 0, y = 304, text = "loss.", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 336, text = "3). You start with a particular number ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 0, y = 352, text = "of BOMBS based on your difficulty level. ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 48, y = 352, text = "BOMBS", color = .Brown},
	{x = 0, y = 368, text = "A BOMB will damage all enemies next to ", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
	{x = 32, y = 368, text = "BOMB", color = .Brown},
	{x = 0, y = 384, text = "you. Use them sparingly!", color = .Gray, shadow = true, shadow_x = 4, shadow_y = 4, shadow_color = .Black},
}

HELP_PAGES := [HELP_PAGE_COUNT]Help_Page {
	{labels = help_labels_0[:]},
	{labels = help_labels_1[:]},
	{labels = help_labels_2[:]},
}
