#pragma once
#include "..\Common\EventHandler.h"
#include "..\Common\CommandProcessorManager.h"
#include "..\Common\ControllerManager.h"
#include "..\Game\GameState.h"
#include "..\Game\Command.h"
class FortuneHunterEventHandler : public tggd::common::EventHandler
{
private:
	GameState& gameState;
	tggd::common::CommandProcessorManager<GameState, Command>& commandProcessors;
	tggd::common::ControllerManager& controllerManager;
	void OnKeyDown(const SDL_KeyboardEvent&);
	void OnJoyAxis(const SDL_JoyAxisEvent&);
	void OnJoyButtonDown(const SDL_JoyButtonEvent&);
	void OnControllerAxis(const SDL_ControllerAxisEvent&);
	void OnControllerButtonDown(const SDL_ControllerButtonEvent&);
public:
	FortuneHunterEventHandler
		(
			tggd::common::CommandProcessorManager<GameState, Command>&,
			tggd::common::ControllerManager&,
			GameState&
		);
	void OnEvent(const SDL_Event&);

};
