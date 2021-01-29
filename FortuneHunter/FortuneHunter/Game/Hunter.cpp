#include "Hunter.h"
Hunter::Hunter()
	: RoomCellObject<TerrainType, ObjectType>()
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

void Hunter::RemoveKey()
{
	keys = (keys > 0) ? (keys - 1) : (keys);
}

const ObjectType& Hunter::GetObjectData() const
{
	return ObjectType::HUNTER;
}

