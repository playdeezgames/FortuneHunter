#pragma once
#include "TerrainType.h"
#include "SpriteTable.h"
class TerrainSprites: public tggd::common::SpriteTable<TerrainType>
{
protected:
	TerrainType StringToIdentifier(const std::string&);
public:
	TerrainSprites(tggd::common::FinishManager&);
};