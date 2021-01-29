#pragma once
#include "Room\RoomCellObject.h"
#include "TerrainType.h"
#include "ObjectType.h"
class Hunter : public RoomCellObject<TerrainType, ObjectType>
{
private:
	size_t keys;
public:
	Hunter();
	size_t GetKeys() const;
	bool HasKey() const;
	void AddKey();
	void RemoveKey();
	const ObjectType& GetObjectData() const;
};
