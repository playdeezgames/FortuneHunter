#include "SpriteManager.h"
#include "Utility.h"
namespace tggd::common
{
	void SpriteManager::AddSprite(const std::string& name, Sprite* sprite)
	{
		sprites[name] = sprite;
	}

	SpriteManager::SpriteManager(FinishManager& finishManager)
		: sprites()
	{
		finishManager.Add(this);
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

	const std::string PROPERTY_TEXTURE = "texture";
	const std::string PROPERTY_OFFSET_X = "offset-x";
	const std::string PROPERTY_OFFSET_Y = "offset-y";
	const std::string PROPERTY_X = "x";
	const std::string PROPERTY_Y = "y";
	const std::string PROPERTY_W = "w";
	const std::string PROPERTY_H = "h";

	void SpriteManager::Start(const TextureManager& textureManager, const std::string& fileName)
	{
		nlohmann::json j = Utility::LoadJSON(fileName);
		for (auto& item : j.items())
		{
			auto& properties = item.value();
			SDL_Texture* texture = textureManager.GetTexture(properties[PROPERTY_TEXTURE]);
			SDL_Rect source;
			source.x = properties[PROPERTY_X];
			source.y = properties[PROPERTY_Y];
			source.w = properties[PROPERTY_W];
			source.h = properties[PROPERTY_H];
			int offsetX = (properties.count(PROPERTY_OFFSET_X) > 0) ? ((int)properties[PROPERTY_OFFSET_X]) : (0);
			int offsetY = (properties.count(PROPERTY_OFFSET_Y) > 0) ? ((int)properties[PROPERTY_OFFSET_Y]) : (0);
			XY<int> offset(offsetX, offsetY);
			Sprite* sprite = new Sprite(texture, source, offset);
			AddSprite(item.key(), sprite);
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
