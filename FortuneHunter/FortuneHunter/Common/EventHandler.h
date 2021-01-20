#pragma once
#include <SDL.h>
namespace tggd::common
{
	class EventHandler
	{
	public:
		virtual bool OnEvent(const SDL_Event&) = 0;
	};
}
