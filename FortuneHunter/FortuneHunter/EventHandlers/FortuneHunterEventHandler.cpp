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
	case SDLK_LEFT:
		commandProcessors.OnCommand(Command::LEFT);
		return;
	case SDLK_RIGHT:
		commandProcessors.OnCommand(Command::RIGHT);
		return;
	case SDLK_ESCAPE:
		commandProcessors.OnCommand(Command::BACK);
		return;
	case SDLK_RETURN:
		commandProcessors.OnCommand(Command::START);
		return;
	case SDLK_SPACE:
		commandProcessors.OnCommand(Command::GREEN);
		return;
	case SDLK_z:
		commandProcessors.OnCommand(Command::BLUE);
		return;
	case SDLK_x:
		commandProcessors.OnCommand(Command::YELLOW);
		return;
	case SDLK_c:
		commandProcessors.OnCommand(Command::RED);
		return;
	case SDLK_COMMA:
		commandProcessors.OnCommand(Command::PREVIOUS);
		return;
	case SDLK_PERIOD:
		commandProcessors.OnCommand(Command::NEXT);
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
	switch ((SDL_GameControllerButton)evt.button)
	{
	case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
		commandProcessors.OnCommand(Command::DOWN);
		return;
	case SDL_CONTROLLER_BUTTON_DPAD_UP:
		commandProcessors.OnCommand(Command::UP);
		return;
	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		commandProcessors.OnCommand(Command::LEFT);
		return;
	case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
		commandProcessors.OnCommand(Command::RIGHT);
		return;
	case SDL_CONTROLLER_BUTTON_A:
		commandProcessors.OnCommand(Command::GREEN);
		return;
	case SDL_CONTROLLER_BUTTON_B:
		commandProcessors.OnCommand(Command::RED);
		return;
	case SDL_CONTROLLER_BUTTON_X:
		commandProcessors.OnCommand(Command::BLUE);
		return;
	case SDL_CONTROLLER_BUTTON_Y:
		commandProcessors.OnCommand(Command::YELLOW);
		return;
	case SDL_CONTROLLER_BUTTON_BACK:
		commandProcessors.OnCommand(Command::BACK);
		return;
	case SDL_CONTROLLER_BUTTON_START:
		commandProcessors.OnCommand(Command::START);
		return;
	case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
		commandProcessors.OnCommand(Command::PREVIOUS);
		return;
	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		commandProcessors.OnCommand(Command::NEXT);
		return;
	}
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
