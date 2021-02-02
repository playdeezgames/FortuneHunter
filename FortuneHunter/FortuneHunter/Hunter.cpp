#include "Hunter.h"
#include "Utility.h"
Hunter::Hunter()
	: RoomCellObject<TerrainType, ObjectType, RoomCellFlags>()
	, keys(0)
	, moves(0)
	, wounds(0)
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
	return tggd::common::Utility::GenerateRandomNumberFromRange(1,5);//TODO: magic numbers
}

void Hunter::AddWounds(int amount)
{
	wounds += amount;
}

int Hunter::GetWounds() const
{
	return wounds;
}

bool Hunter::CanPickUp(ItemType) const
{
	//TODO: determine if can pick up the thing
	return true;
}

void Hunter::PickUp(ItemType) const
{
	//TODO: actually pick up the thing
}
