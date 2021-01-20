#include "FortuneHunterApplication.h"
#include "Constants\Window.h"
#include "Constants\Config.h"
#include "Constants\Color.h"
FortuneHunterApplication FortuneHunterApplication::application;

FortuneHunterApplication::FortuneHunterApplication()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, soundManager()
	, textureManager()
{

}

void FortuneHunterApplication::Start()
{
	textureManager.Start(GetMainRenderer(), Constants::Config::Files::TEXTURES);
	soundManager.Start(Constants::Config::Files::SFX, Constants::Config::Files::MUX);
	SDL_Rect source = { 16, 0, 16, 16 };
}

void FortuneHunterApplication::Finish()
{
	soundManager.Finish();
	textureManager.Finish();
}

void FortuneHunterApplication::Update(int milliSeconds)
{

}

void FortuneHunterApplication::Draw() const
{
	SDL_RenderClear(GetMainRenderer());
}

bool FortuneHunterApplication::OnEvent(const SDL_Event& evt)
{
	switch (evt.type)
	{
	case SDL_QUIT:
		return false;
	default:
		return true;
	}
}
