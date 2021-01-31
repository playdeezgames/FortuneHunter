#pragma once
#include <map>
#include "HealthLevel.h"
#include "SpriteManager.h"
class HealthLevelSprites
{
private:
	std::map<HealthLevel, tggd::common::Sprite*> table;
public:
	HealthLevelSprites();
	void Start(const tggd::common::SpriteManager&, const std::string&);
	void Finish();
	tggd::common::Sprite* GetSprite(HealthLevel) const;
};

