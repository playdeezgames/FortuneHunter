#pragma once
#include "EventHandler.h"
#include "CommandProcessorManager.h"
#include "ControllerManager.h"
#include "UIState.h"
#include "Command.h"
class FortuneHunterEventHandler : public tggd::common::EventHandler
{
private:
	UIState& uiState;
	tggd::common::CommandProcessorManager<UIState, Command>& commandProcessors;
	tggd::common::ControllerManager& controllerManager;
	void OnKeyDown(const SDL_KeyboardEvent&);
	void OnJoyAxis(const SDL_JoyAxisEvent&);
	void OnJoyButtonDown(const SDL_JoyButtonEvent&);
	void OnControllerAxis(const SDL_ControllerAxisEvent&);
	void OnControllerButtonDown(const SDL_ControllerButtonEvent&);
public:
	FortuneHunterEventHandler
		(
			tggd::common::CommandProcessorManager<UIState, Command>&,
			tggd::common::ControllerManager&,
			UIState&
		);
	void OnEvent(const SDL_Event&);

};
