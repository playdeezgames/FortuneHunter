#pragma once
#include "CellConstants.h"
#include "UIConstants.h"
namespace Constants::UI::ConfirmQuit
{
	const int OFFSET_Y = Constants::Cell::HEIGHT * 2;
	const int LINE_HEIGHT = Constants::UI::LINE_HEIGHT;
	const std::string TITLE = "Are you sure you want to quit?";
	const std::string OPTION_YES = "Yes";
	const std::string OPTION_NO = "No";
	const std::string BACKGROUND_SPRITE = "ConfirmQuitBackground";
}
