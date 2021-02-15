#pragma once
#include "XY.h"
#include <string>
#include "SpriteFont.h"
namespace tggd::common
{
	class Label
	{
	private:
		tggd::common::XY<int> xy;
		std::string text;
		const tggd::common::SpriteFont& font;
		SDL_Color color;
	public:
		Label
		(
			const tggd::common::XY<int>&,
			const std::string&,
			const tggd::common::SpriteFont&,
			const SDL_Color&
		);
		void Draw(SDL_Renderer*) const;
	};
}
