#include "SpriteFont.h"
#include "..\Utility.h"
namespace tggd::common
{
	SpriteFont::SpriteFont(const SpriteManager& spriteManager, const std::string& fileName)
		: spriteManager(spriteManager)
		, glyphs()
	{
		nlohmann::json j = Utility::LoadJSON(fileName);
		for (auto& item : j.items())
		{
			char ch = (char)Utility::StringToInt(item.key());
			glyphs[ch] = item.value();
		}
	}

	int SpriteFont::WriteGlyph(SDL_Renderer* renderer, int x, int y, char ch, const SDL_Color& color) const
	{
		auto iter = glyphs.find(ch);
		if (iter != glyphs.end())
		{
			auto sprite = spriteManager.GetSprite(iter->second);
			sprite->Draw(renderer, x, y, color);
			return x + sprite->GetWidth();
		}
		return x;

	}

	int SpriteFont::WriteText(SDL_Renderer* renderer, int x, int y, const std::string& text, const SDL_Color& color) const
	{
		for (auto ch : text)
		{
			x = WriteGlyph(renderer, x, y, ch, color);
		}
		return x;
	}
}
