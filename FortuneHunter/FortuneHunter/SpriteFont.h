#pragma once
#include "SpriteManager.h"
#include <string>
#include <map>
#include "XY.h"
#include "ColorManager.h"
namespace tggd::common
{
	class SpriteFont
	{
	private:
		std::map<char, std::string> glyphs;
		const SpriteManager& spriteManager;
		const ColorManager& colorManager;
	public:
		SpriteFont
		(
			const SpriteManager&, 
			const ColorManager&,
			const std::string&
		);
		tggd::common::XY<int> WriteGlyph(SDL_Renderer*, const tggd::common::XY<int>&, char, const SDL_Color&) const;
		tggd::common::XY<int> WriteText(SDL_Renderer*, const tggd::common::XY<int>&, const std::string&, const SDL_Color&) const;
	};
}

