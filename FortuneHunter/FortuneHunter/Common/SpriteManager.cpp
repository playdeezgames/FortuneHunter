#include "SpriteManager.h"
#include "Utility.h"
namespace tggd::common
{
	void SpriteManager::AddSprite(const std::string& name, Sprite* sprite)
	{
		sprites[name] = sprite;
	}

	SpriteManager::SpriteManager()
		: sprites()
	{

	}

	Sprite* SpriteManager::GetSprite(const std::string& name) const
	{
		auto iter = sprites.find(name);
		if (iter != sprites.end())
		{
			return iter->second;
		}
		return nullptr;
	}

	const int TEXTURE_NAME_INDEX = 0;
	const int TEXTURE_X_INDEX = 1;
	const int TEXTURE_Y_INDEX = 2;
	const int TEXTURE_WIDTH_INDEX = 3;
	const int TEXTURE_HEIGHT_INDEX = 4;
	const char TEXTURE_SEPARATOR = ',';

	void SpriteManager::Start(const TextureManager& textureManager, const std::string& fileName)
	{
		//Character00=romfont8x8,0,0,16,16
		auto resourceMap = Utility::LoadResourceMap(fileName);
		for (auto& entry : resourceMap)
		{
			auto properties = Utility::Tokenize(entry.second, TEXTURE_SEPARATOR);
			SDL_Texture* texture = textureManager.GetTexture(properties[TEXTURE_NAME_INDEX]);
			SDL_Rect source;
			source.x = Utility::StringToInt(properties[TEXTURE_X_INDEX]);
			source.y = Utility::StringToInt(properties[TEXTURE_Y_INDEX]);
			source.w = Utility::StringToInt(properties[TEXTURE_WIDTH_INDEX]);
			source.h = Utility::StringToInt(properties[TEXTURE_HEIGHT_INDEX]);
			Sprite* sprite = new Sprite(texture, source);
			AddSprite(entry.first, sprite);
		}

	}

	void SpriteManager::Finish()
	{
		for (auto& entry : sprites)
		{
			if (entry.second)
			{
				delete entry.second;
				entry.second = nullptr;
			}
		}
		sprites.clear();
	}

}
