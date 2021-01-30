#pragma once
#include <map>
#include <string>
#include "TerrainType.h"
#include "SpriteManager.h"
class TerrainSpriteManager
{
private:
	std::map<TerrainType, const tggd::common::Sprite*> table;
public:
	TerrainSpriteManager();
	void Start(const tggd::common::SpriteManager&,const std::string&);
	const tggd::common::Sprite* Get(TerrainType) const;
};