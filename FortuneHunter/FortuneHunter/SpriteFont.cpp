#include "SpriteFont.h"
#include "Utility.h"
namespace tggd::common
{
	SpriteFont::SpriteFont
	(
		const SpriteManager& spriteManager, 
		const ColorManager& colorManager,
		const std::string& fileName
	)
		: spriteManager(spriteManager)
		, colorManager(colorManager)
		, glyphs()
	{
		nlohmann::json j = Utility::LoadJSON(fileName);
		for (auto& item : j.items())
		{
			char ch = (char)Utility::StringToInt(item.key());
			glyphs[ch] = item.value();
		}
	}

	tggd::common::XY<int> SpriteFont::WriteGlyph(SDL_Renderer* renderer, const tggd::common::XY<int>& xy, char ch, const SDL_Color& color) const
	{
		auto iter = glyphs.find(ch);
		if (iter != glyphs.end())
		{
			auto sprite = spriteManager.GetSprite(iter->second);
			sprite->Draw(renderer, xy, color);
			return XY(xy.GetX() + sprite->GetWidth(), xy.GetY());
		}
		return xy;

	}

	tggd::common::XY<int> SpriteFont::WriteText(SDL_Renderer* renderer, const tggd::common::XY<int>& xy, const std::string& text, const SDL_Color& color) const
	{
		tggd::common::XY<int> temp = xy;
		for (auto ch : text)
		{
			temp = WriteGlyph(renderer, temp, ch, color);
		}
		return temp;
	}
}
