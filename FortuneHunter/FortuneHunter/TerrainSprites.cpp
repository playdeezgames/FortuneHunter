#include "TerrainSprites.h"
#include "Utility.h"
TerrainType TerrainSpriteManager::StringToIdentifier(const std::string& value)
{
	return (TerrainType)tggd::common::Utility::StringToInt(value);
}