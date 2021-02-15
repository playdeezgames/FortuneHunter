#include "Label.h"
namespace tggd::common
{
	Label::Label
	(
		const tggd::common::XY<int>& xy,
		const std::string& text,
		const tggd::common::SpriteFont& font, 
		const SDL_Color& color
	)
		: xy(xy)
		, text(text)
		, font(font)
		, color(color)
	{

	}

	void Label::Draw(SDL_Renderer* renderer) const
	{
		font.WriteText(renderer, xy, text, color);
	}
}
