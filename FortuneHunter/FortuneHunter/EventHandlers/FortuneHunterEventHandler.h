#pragma once
#include "..\Common\EventHandler.h"
#include "..\Common\CommandProcessorManager.h"
#include "..\Common\ControllerManager.h"
#include "..\Game\GameState.h"
#include "..\Game\Command.h"
class FortuneHunterEventHandler : public tggd::common::EventHandler
{
private:
	tggd::common::CommandProcessorManager<GameState, Command>& commandProcessors;
	tggd::common::ControllerManager& controllerManager;
	bool OnKeyDown(const SDL_KeyboardEvent&);
	bool OnJoyAxis(const SDL_JoyAxisEvent&);
	bool OnJoyButtonDown(const SDL_JoyButtonEvent&);
	bool OnControllerAxis(const SDL_ControllerAxisEvent&);
	bool OnControllerButtonDown(const SDL_ControllerButtonEvent&);
public:
	FortuneHunterEventHandler
		(
			tggd::common::CommandProcessorManager<GameState, Command>&,
			tggd::common::ControllerManager&
		);
	bool OnEvent(const SDL_Event&);

};
