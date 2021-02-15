#pragma once
#include <SDL.h>
namespace tggd::common
{
	class Renderer
	{
	protected:
		virtual SDL_Renderer* GetRenderer() const = 0;
	public:
		virtual void Draw() const = 0;
	};
}
