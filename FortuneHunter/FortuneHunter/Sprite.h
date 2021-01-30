#pragma once
#include <SDL.h>
namespace tggd::common
{
	class Sprite
	{
	private:
		SDL_Texture* texture;
		SDL_Rect source;
	public:
		Sprite(SDL_Texture*, const SDL_Rect&);
		void Draw(SDL_Renderer*, int, int, const SDL_Color&) const;
		int GetWidth() const;
	};
}

