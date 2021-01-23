#pragma once
#include "Cell.h"
namespace Constants::UI
{
	const int LINE_HEIGHT = Constants::Cell::HEIGHT;
	namespace MainMenu
	{
		const int OFFSET_Y = Constants::Cell::HEIGHT * 2;
		const int LINE_HEIGHT = Constants::UI::LINE_HEIGHT;
	}
	namespace ConfirmQuit
	{
		const int OFFSET_Y = Constants::Cell::HEIGHT * 2;
		const int LINE_HEIGHT = Constants::UI::LINE_HEIGHT;
	}
	namespace InPlay
	{
		namespace RoomPanel
		{
			const int CLIP_X = 0;
			const int CLIP_Y = 0;
			const int CLIP_WIDTH = 480;
			const int CLIP_HEIGHT = 480;
		}
		namespace StatusPanel
		{
			const int CLIP_X = 480;
			const int CLIP_Y = 0;
			const int CLIP_WIDTH = 160;
			const int CLIP_HEIGHT = 480;
		}

	}
}
