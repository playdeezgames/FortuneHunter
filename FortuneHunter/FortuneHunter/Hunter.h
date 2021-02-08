#pragma once
#include "RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "RoomCellFlags.h"
#include "ItemType.h"
#include "HunterDescriptor.h"
class Hunter : public tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>
{
private:
	const HunterDescriptor& hunterDescriptor;
	size_t keys;
	size_t moves;
	int wounds;
	int diamonds;
	bool exitKey;
	bool exited;
	int armor;
	bool hit;
	size_t bombsUsed;
	size_t maximumHealthLevel;
	size_t maximumArmorLevel;
	size_t maximumAttackLevel;
	void AddDiamond();
	void AddShield();
	void AddPotion();
	void AddExitKey();
	void AddExit();
	void AddKey();
	bool HasKey() const;
	void RemoveKey();
	void SetOffTrap();
public:
	Hunter(const HunterDescriptor&);
	size_t GetKeys() const;
	size_t GetMoves() const;
	void IncrementMoves();
	const ObjectType& GetData() const;
	int GetAttackStrength() const;
	int GetMaximumAttack() const;
	int GetMaximumHealth() const;
	int GetMaximumArmor() const;
	void AddWounds(int);
	int GetHealth() const;
	bool CanPickUp(ItemType) const;
	void PickUp(ItemType);
	int GetDiamonds() const;
	int GetArmor() const;
	void ClearHit();
	bool WasHit() const;
	bool IsAlive() const;
	bool IsWinner() const;
	size_t GetBombs() const;
};
