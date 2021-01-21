#include "FortuneHunterApplication.h"
#include "Constants\Window.h"
#include "Constants\Config.h"
#include "Constants\Color.h"
FortuneHunterApplication FortuneHunterApplication::application;

FortuneHunterApplication::FortuneHunterApplication()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, soundManager()
	, textureManager()
	, gameState(GameState::MAIN_MENU)
	, mainMenuState(MainMenuState::START)
	, eventHandlers(gameState)
	, renderers(gameState)
	, spriteManager()
	, romFont(spriteManager, Constants::Config::Files::ROMFONT)
{

}

void FortuneHunterApplication::Start()
{
	textureManager.Start(GetMainRenderer(), Constants::Config::Files::TEXTURES);
	spriteManager.Start(textureManager, Constants::Config::Files::SPRITES);
	soundManager.Start(Constants::Config::Files::SFX, Constants::Config::Files::MUX);

	eventHandlers.AddEventHandler(GameState::MAIN_MENU, new MainMenuEventHandler(gameState, mainMenuState));

	renderers.AddRenderer(GameState::MAIN_MENU, new MainMenuRenderer(GetMainRenderer(), romFont, mainMenuState));
}

void FortuneHunterApplication::Finish()
{
	soundManager.Finish();
	spriteManager.Finish();
	textureManager.Finish();
	eventHandlers.Finish();
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
	default:
		return eventHandlers.OnEvent(evt);
	}
}
