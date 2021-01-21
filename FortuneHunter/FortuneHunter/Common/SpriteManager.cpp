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

	void SpriteManager::Start(const TextureManager& textureManager, const std::string& fileName)
	{
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
