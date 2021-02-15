#pragma once
#include <SDL.h>
#include "XY.h"
namespace tggd::common
{
	class Sprite
	{
	private:
		SDL_Texture* texture;
		SDL_Rect source;
		XY<int> offset;
	public:
		Sprite(SDL_Texture*, const SDL_Rect&, const XY<int>&);
		void Draw(SDL_Renderer*, const XY<int>&, const SDL_Color*) const;
		void Draw(SDL_Renderer*, const XY<int>&) const;
		int GetWidth() const;
	};
}

