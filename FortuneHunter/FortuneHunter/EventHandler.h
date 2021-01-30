#pragma once
#include <SDL.h>
namespace tggd::common
{
	class EventHandler
	{
	public:
		virtual void OnEvent(const SDL_Event&) = 0;
	};
}
