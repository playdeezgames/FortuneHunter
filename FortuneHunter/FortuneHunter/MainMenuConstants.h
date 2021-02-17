#pragma once
#include "CellConstants.h"
#include "UIConstants.h"
#include <string>
namespace Constants::UI::MainMenu
{
	const int TITLE_OFFSET_X = 320;
	const int TITLE_OFFSET_Y = 76;
	const int MENU_OFFSET_X = 320;
	const int MENU_OFFSET_Y = 168;
	const int LINE_HEIGHT = Constants::UI::LINE_HEIGHT * 3 / 2;
	const std::string TITLE = "Welcome to Fortune Hunter!";
	const std::string OPTION_START = "Start";
	const std::string OPTION_CONTINUE = "Continue";
	const std::string OPTION_INSTRUCTIONS = "Instructions";
	const std::string OPTION_STATISTICS = "Statistics";
	const std::string OPTION_ABOUT = "About";
	const std::string OPTION_OPTIONS = "Options";
	const std::string OPTION_QUIT = "Quit";
}