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

	tggd::common::Sprite* SpriteFont::GetGlyphSprite(char ch) const
	{
		auto iter = glyphs.find(ch);
		if (iter != glyphs.end())
		{
			return spriteManager.GetSprite(iter->second);
		}
		return nullptr;
	}



	tggd::common::XY<int> SpriteFont::WriteGlyph(SDL_Renderer* renderer, const tggd::common::XY<int>& xy, char ch, const std::string& color) const
	{
		auto sprite = GetGlyphSprite(ch);
		if (sprite)
		{
			sprite->Draw(renderer, xy, colorManager.GetDescriptor(color));
			return XY(xy.GetX() + sprite->GetWidth(), xy.GetY());
		}
		return xy;

	}

	tggd::common::XY<int> SpriteFont::WriteText(SDL_Renderer* renderer, const tggd::common::XY<int>& xy, const std::string& text, const std::string& color) const
	{
		tggd::common::XY<int> temp = xy;
		for (auto ch : text)
		{
			temp = WriteGlyph(renderer, temp, ch, color);
		}
		return temp;
	}

	void SpriteFont::WriteTextCentered(SDL_Renderer* renderer, const tggd::common::XY<int>& xy, const std::string& text, const std::string& color) const
	{
		int width = 0;
		for (auto ch : text)
		{
			auto sprite = GetGlyphSprite(ch);
			if (sprite)
			{
				width += sprite->GetWidth();
			}
		}
		auto adjustedXY = tggd::common::XY<int>(xy.GetX() - width / 2, xy.GetY());
		WriteText(renderer, adjustedXY, text, color);
	}

}
