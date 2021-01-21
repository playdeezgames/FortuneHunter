#pragma once
#include "..\Common\EventHandler.h"
class MainMenuEventHandler : public tggd::common::EventHandler
{
public:
	bool OnEvent(const SDL_Event&);
};

