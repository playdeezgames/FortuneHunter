#include "FortuneHunterApplication.h"
#include "Constants\Window.h"
#include "Constants\Config.h"
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

}

bool FortuneHunterApplication::OnEvent(const SDL_Event& evt)
{
	switch (evt.type)
	{
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		if (evt.key.keysym.sym == SDLK_SPACE)
		{
			soundManager.PlaySound("ting");
		}
		return true;
	default:
		return true;
	}
}
