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
	, eventHandlers(gameState)
{

}

void FortuneHunterApplication::Start()
{
	textureManager.Start(GetMainRenderer(), Constants::Config::Files::TEXTURES);
	spriteManager.Start(textureManager, Constants::Config::Files::SPRITES);
	soundManager.Start(Constants::Config::Files::SFX, Constants::Config::Files::MUX);
	eventHandlers.AddEventHandler(GameState::MAIN_MENU, new MainMenuEventHandler());
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
	spriteManager.GetSprite("Character02")->Draw(GetMainRenderer(), 0, 0, Constants::Color::WHITE);
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
