#pragma once
#include "RoomPanelConstants.h"
#include "CellConstants.h"
namespace Constants::UI::StatusPanel
{
	const int CLIP_X = Constants::UI::RoomPanel::CLIP_X + Constants::UI::RoomPanel::CLIP_WIDTH;
	const int CLIP_Y = 0;
	const int CLIP_WIDTH = 160;
	const int CLIP_HEIGHT = 480;

	const int MOVE_ICON_X = CLIP_X;
	const int MOVE_ICON_Y = CLIP_Y;
	const int MOVE_TEXT_X = MOVE_ICON_X + Constants::Cell::WIDTH;
	const int MOVE_TEXT_Y = MOVE_ICON_Y;
	const std::string MOVE_ICON_SPRITE_NAME = "MoveIcon";

	const int DIAMOND_ICON_X = MOVE_ICON_X;
	const int DIAMOND_ICON_Y = MOVE_ICON_Y + Constants::Cell::HEIGHT;
	const int DIAMOND_TEXT_X = DIAMOND_ICON_X + Constants::Cell::WIDTH;
	const int DIAMOND_TEXT_Y = DIAMOND_ICON_Y;
	const std::string DIAMOND_ICON_SPRITE_NAME = "DiamondItem";

	const int ATTACK_ICON_X = MOVE_ICON_X;
	const int ATTACK_ICON_Y = DIAMOND_ICON_Y + Constants::Cell::HEIGHT;
	const int ATTACK_TEXT_X = ATTACK_ICON_X + Constants::Cell::WIDTH;
	const int ATTACK_TEXT_Y = ATTACK_ICON_Y;
	const std::string ATTACK_ICON_SPRITE_NAME = "SwordItem";

	const int ARMOR_ICON_X = MOVE_ICON_X;
	const int ARMOR_ICON_Y = ATTACK_ICON_Y + Constants::Cell::HEIGHT;
	const int ARMOR_TEXT_X = ARMOR_ICON_X + Constants::Cell::WIDTH;
	const int ARMOR_TEXT_Y = ARMOR_ICON_Y;
	const std::string ARMOR_ICON_SPRITE_NAME = "ShieldItem";

	const int HEALTH_ICON_X = MOVE_ICON_X;
	const int HEALTH_ICON_Y = ARMOR_ICON_Y + Constants::Cell::HEIGHT;
	const int HEALTH_TEXT_X = HEALTH_ICON_X + Constants::Cell::WIDTH;
	const int HEALTH_TEXT_Y = HEALTH_ICON_Y;
	const std::string HEALTH_ICON_SPRITE_NAME = "PotionItem";

	const int KEYS_ICON_X = MOVE_ICON_X;
	const int KEYS_ICON_Y = HEALTH_ICON_Y + Constants::Cell::HEIGHT;
	const int KEYS_TEXT_X = KEYS_ICON_X + Constants::Cell::WIDTH;
	const int KEYS_TEXT_Y = KEYS_ICON_Y;
	const std::string KEYS_ICON_SPRITE_NAME = "KeyItem";

	const int BOMBS_ICON_X = MOVE_ICON_X;
	const int BOMBS_ICON_Y = KEYS_ICON_Y + Constants::Cell::HEIGHT;
	const int BOMBS_TEXT_X = BOMBS_ICON_X + Constants::Cell::WIDTH;
	const int BOMBS_TEXT_Y = BOMBS_ICON_Y;
	const std::string BOMBS_ICON_SPRITE_NAME = "Bombs";

}

