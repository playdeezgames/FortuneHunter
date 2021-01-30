#pragma once
#include <SDL.h>
#include <map>
#include <string>
namespace tggd::common
{
	class TextureManager
	{
	private:
		std::map<std::string, SDL_Texture*> textures;
		void AddTexture(const std::string&, SDL_Texture*);
	public:
		TextureManager();
		void Start(SDL_Renderer*, const std::string&);
		void Finish();
		SDL_Texture* GetTexture(const std::string&) const;
	};
}

