#include "TextureManager.h"
#include "Utility.h"
#include <SDL_image.h>
namespace tggd::common
{
	TextureManager::TextureManager(FinishManager& finishManager)
		: textures()
	{
		finishManager.Add(this);
	}

	void TextureManager::Start(SDL_Renderer* renderer, const std::string& fileName)
	{
		auto j = Utility::LoadJSON(fileName);
		for (auto& entry : j.items())
		{
			std::string imageFileName = entry.value();
			AddTexture(entry.key(), IMG_LoadTexture(renderer, imageFileName.c_str()));
		}
	}

	void TextureManager::Finish()
	{
		for (auto& entry : textures)
		{
			if (entry.second)
			{
				SDL_DestroyTexture(entry.second);
				entry.second = nullptr;
			}
		}
		textures.clear();
	}

	SDL_Texture* TextureManager::GetTexture(const std::string& name) const
	{
		auto iter = textures.find(name);
		if (iter != textures.end())
		{
			return iter->second;
		}
		return nullptr;
	}

	void TextureManager::AddTexture(const std::string& name, SDL_Texture* texture)
	{
		textures[name] = texture;
	}
}