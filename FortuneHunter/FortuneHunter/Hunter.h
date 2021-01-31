#pragma once
#include "RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
#include "RoomCellFlags.h"
class Hunter : public tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>
{
private:
	size_t keys;
	size_t moves;
	int wounds;
public:
	Hunter();
	size_t GetKeys() const;
	size_t GetMoves() const;
	void IncrementMoves();
	bool HasKey() const;
	void AddKey();
	void RemoveKey();
	const ObjectType& GetData() const;
	int GetAttackStrength() const;
	void AddWounds(int);
	int GetWounds() const;
};
