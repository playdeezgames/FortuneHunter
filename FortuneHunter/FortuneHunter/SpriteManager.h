#pragma once
#include <map>
#include <string>
#include "Sprite.h"
#include "TextureManager.h"
#include "FinishManager.h"
namespace tggd::common
{
	class SpriteManager: public Finisher
	{
	private:
		std::map<std::string, Sprite*> sprites;
		void AddSprite(const std::string&, Sprite*);
	public:
		SpriteManager(FinishManager&);
		Sprite* GetSprite(const std::string&) const;
		void Start(const TextureManager&, const std::string&);
		void Finish();
	};
}