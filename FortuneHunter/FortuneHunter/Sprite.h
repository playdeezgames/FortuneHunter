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
		void Draw(SDL_Renderer*, int, int, const SDL_Color&) const;
		int GetWidth() const;
	};
}

