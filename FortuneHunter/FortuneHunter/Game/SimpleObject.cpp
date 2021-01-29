#include "SimpleObject.h"
SimpleObject::SimpleObject(ObjectType objectType)
	: RoomCellObject<TerrainType, ObjectType>()
	, objectType(objectType)
{

}

const ObjectType& SimpleObject::GetObjectData() const
{
	return objectType;
}
