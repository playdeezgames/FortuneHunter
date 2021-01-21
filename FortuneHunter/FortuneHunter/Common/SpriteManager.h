#pragma once
#include <map>
#include <string>
#include "Sprite.h"
#include "TextureManager.h"
namespace tggd::common
{
	class SpriteManager
	{
	private:
		std::map<std::string, Sprite*> sprites;
		void AddSprite(const std::string&, Sprite*);
	public:
		SpriteManager();
		Sprite* GetSprite(const std::string&) const;
		void Start(const TextureManager&, const std::string&);
		void Finish();
	};
}