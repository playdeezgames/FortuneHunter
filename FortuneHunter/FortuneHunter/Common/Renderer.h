#pragma once
#include <SDL.h>
namespace tggd::common
{
	class Renderer
	{
	protected:
		virtual SDL_Renderer* GetMainRenderer() const = 0;
	public:
		virtual void Draw() = 0;
	};
}
