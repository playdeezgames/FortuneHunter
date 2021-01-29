#include "CreatureDescriptor.h"
CreatureDescriptor::CreatureDescriptor
(
	ObjectType objectType,
	size_t numberAppearing
)
	: objectType(objectType)
	, numberAppearing(numberAppearing)
{

}

ObjectType CreatureDescriptor::GetObjectType() const
{
	return objectType;
}

size_t CreatureDescriptor::GetNumberAppearing() const
{
	return numberAppearing;
}
