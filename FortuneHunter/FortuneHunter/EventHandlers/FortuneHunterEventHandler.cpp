#include "FortuneHunterEventHandler.h"
FortuneHunterEventHandler::FortuneHunterEventHandler
	(
		tggd::common::CommandProcessorManager<GameState, Command>& commandProcessors,
		tggd::common::ControllerManager& controllerManager,
		GameState& gameState
	)
	: commandProcessors(commandProcessors)
	, controllerManager(controllerManager)
	, gameState(gameState)
{

}

void FortuneHunterEventHandler::OnKeyDown(const SDL_KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_UP:
		commandProcessors.OnCommand(Command::UP);
		return;
	case SDLK_DOWN:
		commandProcessors.OnCommand(Command::DOWN);
		return;
	}
}

void FortuneHunterEventHandler::OnJoyAxis(const SDL_JoyAxisEvent& evt)
{
	if (!controllerManager.IsController(evt.which))
	{
	}
}

void FortuneHunterEventHandler::OnJoyButtonDown(const SDL_JoyButtonEvent& evt)
{
	if (!controllerManager.IsController(evt.which))
	{
	}
}

void FortuneHunterEventHandler::OnControllerAxis(const SDL_ControllerAxisEvent& evt)
{
}

void FortuneHunterEventHandler::OnControllerButtonDown(const SDL_ControllerButtonEvent& evt)
{
}

void FortuneHunterEventHandler::OnEvent(const SDL_Event& evt)
{
	switch (evt.type)
	{
	case SDL_QUIT:
		gameState = GameState::QUIT;
		return;
	case SDL_KEYDOWN:
		OnKeyDown(evt.key);
		return;
	case SDL_JOYAXISMOTION:
		OnJoyAxis(evt.jaxis);
		return;
	case SDL_JOYBUTTONDOWN:
		OnJoyButtonDown(evt.jbutton);
		return;
	case SDL_CONTROLLERAXISMOTION:
		OnControllerAxis(evt.caxis);
		return;
	case SDL_CONTROLLERBUTTONDOWN:
		OnControllerButtonDown(evt.cbutton);
		return;
	}
}
