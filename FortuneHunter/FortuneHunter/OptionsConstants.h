#pragma once
#include "CellConstants.h"
#include "UIConstants.h"
#include <string>
namespace Constants::UI::Options
{
	const int OFFSET_Y = Constants::Cell::HEIGHT * 2;
	const int LINE_HEIGHT = Constants::UI::LINE_HEIGHT;
	const std::string TITLE = "Options";
	const std::string OPTION_MUTE_ON = "Unmute";
	const std::string OPTION_MUTE_OFF = "Mute";
	const std::string OPTION_SFX_VOLUME = "SFX Volume";
	const std::string OPTION_MUX_VOLUME = "MUX Volume";
	const std::string OPTION_BACK = "Main Menu";
}
