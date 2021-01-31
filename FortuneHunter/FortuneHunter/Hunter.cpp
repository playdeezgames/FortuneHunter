#include "Hunter.h"
Hunter::Hunter()
	: RoomCellObject<TerrainType, ObjectType, RoomCellFlags>()
	, keys(0)
	, moves(0)
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

const ObjectType& Hunter::GetData() const
{
	static ObjectType dummy = ObjectType::HUNTER;
	return dummy;
}

size_t Hunter::GetMoves() const
{
	return moves;
}

void Hunter::IncrementMoves()
{
	moves++;
}

int Hunter::GetAttackStrength() const
{
	return 1;//TODO: magic string
}

void Hunter::AddWounds(int amount)
{
	//TODO: implement me!
}
