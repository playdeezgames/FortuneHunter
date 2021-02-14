#pragma once
#include "CellConstants.h"
#include "UIConstants.h"
#include <string>
namespace Constants::UI::Options
{
	const int TITLE_OFFSET_X = 8;
	const int TITLE_OFFSET_Y = 80;
	const int MENU_OFFSET_X = 12 * 16;
	const int MENU_OFFSET_Y = 240 - 4 * 16;
	const int LINE_HEIGHT = Constants::UI::LINE_HEIGHT * 2;
	const std::string TITLE = "              ==Options==";
	const std::string OPTION_MUTE_ON = "     Unmute";
	const std::string OPTION_MUTE_OFF = "      Mute";
	const std::string OPTION_SFX_VOLUME = "SFX Volume";
	const std::string OPTION_MUX_VOLUME = "MUX Volume";
	const std::string OPTION_BACK = "    Main Menu";
}
