#pragma once
#include "TerrainType.h"
#include "SpriteTable.h"
class TerrainSpriteManager: public tggd::common::SpriteTable<TerrainType>
{
protected:
	TerrainType StringToIdentifier(const std::string&);
};