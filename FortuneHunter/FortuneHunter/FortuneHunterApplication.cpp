#include "FortuneHunterApplication.h"
#include "Constants\Window.h"
#include "Constants\Config.h"
#include "Constants\Color.h"
#include "CommandProcessors\MainMenuCommandProcessor.h"
FortuneHunterApplication FortuneHunterApplication::application;

FortuneHunterApplication::FortuneHunterApplication()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, soundManager()
	, textureManager()
	, gameState(GameState::MAIN_MENU)
	, mainMenuState(MainMenuState::START)
	, renderers(gameState)
	, spriteManager()
	, romFont(spriteManager, Constants::Config::Files::ROMFONT)
	, controllerManager()
	, commandProcessors(gameState)
{

}

void FortuneHunterApplication::Start()
{
	controllerManager.Start();

	textureManager.Start(GetMainRenderer(), Constants::Config::Files::TEXTURES);
	spriteManager.Start(textureManager, Constants::Config::Files::SPRITES);
	soundManager.Start(Constants::Config::Files::SFX, Constants::Config::Files::MUX);

	commandProcessors.AddCommandProcessor(GameState::MAIN_MENU, new MainMenuCommandProcessor(gameState, mainMenuState));

	renderers.AddRenderer(GameState::MAIN_MENU, new MainMenuRenderer(GetMainRenderer(), romFont, mainMenuState));
}

void FortuneHunterApplication::Finish()
{
	commandProcessors.Finish();
	soundManager.Finish();
	spriteManager.Finish();
	textureManager.Finish();
	controllerManager.Finish();
}

void FortuneHunterApplication::Update(int milliSeconds)
{

}

void FortuneHunterApplication::Draw() const
{
	SDL_RenderClear(GetMainRenderer());
	renderers.Draw();
}

bool FortuneHunterApplication::OnKeyDown(const SDL_KeyboardEvent& evt)
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

bool FortuneHunterApplication::OnJoyAxis(const SDL_JoyAxisEvent& evt)
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

bool FortuneHunterApplication::OnJoyButtonDown(const SDL_JoyButtonEvent& evt)
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

bool FortuneHunterApplication::OnControllerAxis(const SDL_ControllerAxisEvent& evt)
{
	return true;
}

bool FortuneHunterApplication::OnControllerButtonDown(const SDL_ControllerButtonEvent& evt)
{
	return true;
}



bool FortuneHunterApplication::OnEvent(const SDL_Event& evt)
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
