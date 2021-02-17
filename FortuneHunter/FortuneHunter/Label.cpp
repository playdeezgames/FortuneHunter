#include "Label.h"
namespace tggd::common
{
	Label::Label
	(
		const tggd::common::XY<int>& xy,
		const std::string& text,
		const tggd::common::SpriteFont& font, 
		const std::string& color,
		bool hasDropShadow,
		const tggd::common::XY<int>& dropShadowOffset,
		const std::string& dropShadowColor
	)
		: xy(xy)
		, text(text)
		, font(font)
		, color(color)
		, hasDropShadow(hasDropShadow)
		, dropShadowXY(dropShadowOffset + xy)
		, dropShadowColor(dropShadowColor)
	{

	}
	void Label::Draw(SDL_Renderer* renderer) const
	{
		if (hasDropShadow)
		{
			font.WriteText(renderer, dropShadowXY, text, dropShadowColor);
		}
		font.WriteText(renderer, xy, text, color);
	}
}
