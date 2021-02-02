#pragma once
#include <SDL.h>
#include <map>
#include <string>
#include "FinishManager.h"
namespace tggd::common
{
	class TextureManager: public Finisher
	{
	private:
		std::map<std::string, SDL_Texture*> textures;
		void AddTexture(const std::string&, SDL_Texture*);
	public:
		TextureManager(FinishManager&);
		void Start(SDL_Renderer*, const std::string&);
		void Finish();
		SDL_Texture* GetTexture(const std::string&) const;
	};
}

