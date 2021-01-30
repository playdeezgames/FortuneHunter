#pragma once
#include "RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
class Hunter : public tggd::common::RoomCellObject<TerrainType, ObjectType>
{
private:
	size_t keys;
	size_t moves;
public:
	Hunter();
	size_t GetKeys() const;
	size_t GetMoves() const;
	void IncrementMoves();
	bool HasKey() const;
	void AddKey();
	void RemoveKey();
	const ObjectType& GetData() const;
};