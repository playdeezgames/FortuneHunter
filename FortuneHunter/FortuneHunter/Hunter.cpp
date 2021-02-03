#include "Hunter.h"
#include "Utility.h"
Hunter::Hunter()
	: RoomCellObject<TerrainType, ObjectType, RoomCellFlags>()
	, keys(0)
	, moves(0)
	, wounds(0)
	, armor(0)
	, exitKey(false)
	, exited(false)
	, diamonds(0)
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
	int absorbed = (armor > amount) ? (amount) : (armor - amount);
	amount -= absorbed;
	armor -= absorbed;
	wounds += amount;
}

int Hunter::GetWounds() const
{
	return wounds;
}

bool Hunter::CanPickUp(ItemType itemType) const
{
	switch (itemType)
	{
	case ItemType::EXIT:
		return exitKey;
	case ItemType::DOOR_EW:
	case ItemType::DOOR_NS:
		return GetKeys()>0;
	default:
		return true;
	}
}

void Hunter::PickUp(ItemType itemType)
{
	switch (itemType)
	{
	case ItemType::KEY:
		AddKey();
		break;
	case ItemType::EXIT_KEY:
		AddExitKey();
		break;
	case ItemType::DIAMOND:
		AddDiamond();
		break;
	case ItemType::POTION:
		AddPotion();
		break;
	case ItemType::SHIELD:
		AddShield();
		break;
	case ItemType::EXIT:
		AddExit();
		break;
	}
}

int Hunter::GetDiamonds() const
{
	return diamonds;
}

int Hunter::GetArmor() const
{
	return armor;
}

void Hunter::AddDiamond()
{
	diamonds++;
}
void Hunter::AddShield()
{
	armor += 10;//TODO: magic number
	if (armor > 25)//TODO: magic number
	{
		armor = 25;//TODO: magic number
	}
}

void Hunter::AddPotion()
{
	wounds -= 10;//TODO: magic number
	if (wounds < 0)
	{
		wounds = 0;
	}
}

void Hunter::AddExitKey()
{
	exitKey = true;
}

void Hunter::AddExit()
{
	exited = true;
}

