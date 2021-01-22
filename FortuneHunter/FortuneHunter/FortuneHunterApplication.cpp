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

bool FortuneHunterApplication::OnEvent(const SDL_Event& evt)
{
	switch (evt.type)
	{
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		switch (evt.key.keysym.sym)
		{
		case SDLK_UP:
			commandProcessors.OnCommand(Command::UP);
			return true;
		case SDLK_DOWN:
			commandProcessors.OnCommand(Command::DOWN);
			return true;
		}
		return true;
	default:
		return true;
	}
}
