#pragma once
#include "..\Managers\SpriteManager.h"
#include <string>
#include <map>
namespace tggd::common
{
	class SpriteFont
	{
	private:
		std::map<char, std::string> glyphs;
		const SpriteManager& spriteManager;
	public:
		SpriteFont(const SpriteManager&, const std::string&);
		int WriteGlyph(SDL_Renderer*, int, int, char, const SDL_Color&) const;
		int WriteText(SDL_Renderer*, int, int, const std::string&, const SDL_Color&) const;
	};
}

