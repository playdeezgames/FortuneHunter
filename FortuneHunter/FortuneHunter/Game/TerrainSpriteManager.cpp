#include "TerrainSpriteManager.h"
#include "..\Common\Utility.h"
#include "..\Common\Utility.h"
TerrainSpriteManager::TerrainSpriteManager()
	: table()
{
}

void TerrainSpriteManager::Start(const tggd::common::SpriteManager& spriteManager, const std::string& fileName)
{
	nlohmann::json j = tggd::common::Utility::LoadJSON(fileName);
	for (auto& entry : j.items())
	{
		TerrainType terrainType = (TerrainType)tggd::common::Utility::StringToInt(entry.key());
		table[terrainType] = spriteManager.GetSprite(entry.value());
	}
}

const tggd::common::Sprite* TerrainSpriteManager::Get(TerrainType terrainType) const
{
	return table.find(terrainType)->second;
}
