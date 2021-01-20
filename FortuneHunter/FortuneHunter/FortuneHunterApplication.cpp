#include "FortuneHunterApplication.h"
FortuneHunterApplication FortuneHunterApplication::application;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "Fortune Hunter";

FortuneHunterApplication::FortuneHunterApplication()
	: Application(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
	, soundManager()
{

}

void FortuneHunterApplication::Start()
{

}

void FortuneHunterApplication::Finish()
{

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
	default:
		return true;
	}
}
