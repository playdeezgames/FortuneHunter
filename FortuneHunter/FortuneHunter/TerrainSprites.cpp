#include "TerrainSprites.h"
#include "Utility.h"
TerrainType TerrainSprites::StringToIdentifier(const std::string& value)
{
	return (TerrainType)tggd::common::Utility::StringToInt(value);
}

TerrainSprites::TerrainSprites(tggd::common::FinishManager& finishManager)
	: SpriteTable(finishManager)
{

}
