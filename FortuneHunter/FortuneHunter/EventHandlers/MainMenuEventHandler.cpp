#include "MainMenuEventHandler.h"
bool MainMenuEventHandler::OnEvent(const SDL_Event& evt)
{
	if (evt.type == SDL_KEYDOWN)
	{
		switch (evt.key.keysym.sym)
		{
		case SDLK_UP:
			mainMenuState = PreviousMainMenuState(mainMenuState);
			return true;
		case SDLK_DOWN:
			mainMenuState = NextMainMenuState(mainMenuState);
			return true;
		case SDLK_SPACE:
			return mainMenuState != MainMenuState::QUIT;
		}
	}
	return true;
}

MainMenuEventHandler::MainMenuEventHandler(GameState& gameState, MainMenuState& mainMenuState)
	: mainMenuState(mainMenuState)
	, gameState(gameState)
{

}