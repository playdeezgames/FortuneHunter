#include "Hunter.h"
Hunter::Hunter()
	: RoomCellObject<TerrainType, ObjectType>(ObjectType::HUNTER)
	, keys(0)
{

}

size_t Hunter::GetKeys() const
{
	return keys;
}

void Hunter::AddKey()
{
	keys++;
}

bool Hunter::HasKey() const
{
	return keys > 0;
}
