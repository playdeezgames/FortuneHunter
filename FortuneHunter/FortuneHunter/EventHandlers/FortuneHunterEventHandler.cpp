#include "FortuneHunterEventHandler.h"
FortuneHunterEventHandler::FortuneHunterEventHandler
	(
		tggd::common::CommandProcessorManager<GameState, Command>& commandProcessors,
		tggd::common::ControllerManager& controllerManager
	)
	: commandProcessors(commandProcessors)
	, controllerManager(controllerManager)
{

}

bool FortuneHunterEventHandler::OnKeyDown(const SDL_KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_UP:
		commandProcessors.OnCommand(Command::UP);
		return true;
	case SDLK_DOWN:
		commandProcessors.OnCommand(Command::DOWN);
		return true;
	}
	return true;
}

bool FortuneHunterEventHandler::OnJoyAxis(const SDL_JoyAxisEvent& evt)
{
	if (controllerManager.IsController(evt.which))
	{
		return true;//it should be handled by the game controller events, not here
	}
	else
	{
		return true;
	}
}

bool FortuneHunterEventHandler::OnJoyButtonDown(const SDL_JoyButtonEvent& evt)
{
	if (controllerManager.IsController(evt.which))
	{
		return true;//it should be handled by the game controller events, not here
	}
	else
	{
		return true;
	}
}

bool FortuneHunterEventHandler::OnControllerAxis(const SDL_ControllerAxisEvent& evt)
{
	return true;
}

bool FortuneHunterEventHandler::OnControllerButtonDown(const SDL_ControllerButtonEvent& evt)
{
	return true;
}



bool FortuneHunterEventHandler::OnEvent(const SDL_Event& evt)
{
	switch (evt.type)
	{
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		return OnKeyDown(evt.key);
	case SDL_JOYAXISMOTION:
		return OnJoyAxis(evt.jaxis);
	case SDL_JOYBUTTONDOWN:
		return OnJoyButtonDown(evt.jbutton);
	case SDL_CONTROLLERAXISMOTION:
		return OnControllerAxis(evt.caxis);
	case SDL_CONTROLLERBUTTONDOWN:
		return OnControllerButtonDown(evt.cbutton);
	default:
		return true;
	}
}
