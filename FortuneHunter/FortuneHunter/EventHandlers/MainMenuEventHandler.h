#pragma once
#include "..\Common\EventHandler.h"
#include "..\Game\MainMenuState.h"
#include "..\Game\GameState.h"
class MainMenuEventHandler : public tggd::common::EventHandler
{
private:
	GameState& gameState;
	MainMenuState& mainMenuState;
public:
	MainMenuEventHandler(GameState&, MainMenuState&);
	bool OnEvent(const SDL_Event&);
};

