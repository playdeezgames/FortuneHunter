#include "Sprite.h"
namespace tggd::common
{
	Sprite::Sprite(SDL_Texture* texture, const SDL_Rect& source)
		: texture(texture)
		, source(source)
	{

	}

	void Sprite::Draw(SDL_Renderer* renderer, int x, int y, const SDL_Color& color) const
	{
		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
		SDL_Rect rcDst =
		{
			x,
			y,
			source.w,
			source.h
		};
		SDL_RenderCopy(renderer, texture, &source, &rcDst);
	}

}
