#include "HealthLevelSprites.h"
#include "Utility.h"
HealthLevelSprites::HealthLevelSprites()
	: table()
{

}

void HealthLevelSprites::Start(const tggd::common::SpriteManager& spriteManager, const std::string& fileName)
{
	nlohmann::json j = tggd::common::Utility::LoadJSON(fileName);
	for (auto& entry : j.items())
	{
		HealthLevel terrainType = (HealthLevel)tggd::common::Utility::StringToInt(entry.key());
		table[terrainType] = spriteManager.GetSprite(entry.value());
	}
}

tggd::common::Sprite* HealthLevelSprites::GetSprite(HealthLevel level) const
{
	auto iter = table.find(level);
	if (iter != table.end())
	{
		return iter->second;
	}
	return nullptr;
}

void HealthLevelSprites::Finish()
{
	table.clear();
}
