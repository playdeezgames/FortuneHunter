#pragma once
#include "CellConstants.h"
#include "UIConstants.h"
#include <string>
namespace Constants::UI::MainMenu
{
	const int OFFSET_Y = Constants::Cell::HEIGHT * 2;
	const int LINE_HEIGHT = Constants::UI::LINE_HEIGHT;
	const std::string TITLE = "Welcome to Fortune Hunter!";
	const std::string OPTION_START = "Start";
	const std::string OPTION_CONTINUE = "Continue";
	const std::string OPTION_INSTRUCTIONS = "Instructions(TODO)";
	const std::string OPTION_ABOUT = "About(TODO)";
	const std::string OPTION_OPTIONS = "Options";
	const std::string OPTION_QUIT = "Quit";
}