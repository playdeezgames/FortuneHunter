#include "Hunter.h"
#include "Utility.h"
Hunter::Hunter(const HunterDescriptor& hunterDescriptor)
	: RoomCellObject<TerrainType, ObjectType, RoomCellFlags>()
	, hunterDescriptor(hunterDescriptor)
	, keys(0)
	, moves(0)
	, wounds(0)
	, armor(0)
	, exitKey(false)
	, exited(false)
	, diamonds(0)
	, maximumArmorLevel(0)
	, maximumAttackLevel(0)
	, maximumHealthLevel(0)
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
	return tggd::common::Utility::GenerateRandomNumberFromRange
	(
		1,
		hunterDescriptor.GetMaximumAttack(maximumAttackLevel)
	);
}

void Hunter::AddWounds(int amount)
{
	int absorbed = (armor >= amount) ? (amount) : (0);
	amount -= absorbed;
	armor -= absorbed;
	wounds += amount;
	if (wounds > GetMaximumHealth())
	{
		wounds = GetMaximumHealth();
	}
}

int Hunter::GetHealth() const
{
	return GetMaximumHealth() - wounds;
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
	case ItemType::DOOR_EW:
	case ItemType::DOOR_NS:
		RemoveKey();
		break;
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
	case ItemType::ARMOR_UPGRADE:
		maximumArmorLevel++;
		break;
	case ItemType::ATTACK_UPGRADE:
		maximumAttackLevel++;
		break;
	case ItemType::HEALTH_UPGRADE:
		maximumHealthLevel++;
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
	int maximumArmor = hunterDescriptor.GetMaximumArmor(maximumArmorLevel);
	if (armor > maximumArmor)
	{
		armor = maximumArmor;
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

int Hunter::GetMaximumHealth() const
{
	return hunterDescriptor.GetMaximumHealth(maximumHealthLevel);
}

bool Hunter::IsAlive() const
{
	return GetHealth() > 0;
}

int Hunter::GetMaximumArmor() const
{
	return hunterDescriptor.GetMaximumArmor(maximumArmorLevel);
}

int Hunter::GetMaximumAttack() const
{
	return hunterDescriptor.GetMaximumAttack(maximumAttackLevel);
}

bool Hunter::IsWinner() const
{
	return exited;
}
