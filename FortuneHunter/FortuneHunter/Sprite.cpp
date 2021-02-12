#include "Sprite.h"
namespace tggd::common
{
	Sprite::Sprite
	(
		SDL_Texture* texture,
		const SDL_Rect& source,
		const XY<int>& offset
	)
		: texture(texture)
		, source(source)
		, offset(offset)
	{

	}

	void Sprite::Draw(SDL_Renderer* renderer, const XY<int>& xy, const SDL_Color& color) const
	{
		SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
		SDL_Rect rcDst =
		{
			xy.GetX() + offset.GetX(),
			xy.GetY() + offset.GetY(),
			source.w,
			source.h
		};
		SDL_RenderCopy(renderer, texture, &source, &rcDst);
	}

	int Sprite::GetWidth() const
	{
		return source.w;
	}

}
