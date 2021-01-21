#include "MainMenuEventHandler.h"
bool MainMenuEventHandler::OnEvent(const SDL_Event& evt)
{
	if (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE)
	{
		return false;
	}
	return true;
}
