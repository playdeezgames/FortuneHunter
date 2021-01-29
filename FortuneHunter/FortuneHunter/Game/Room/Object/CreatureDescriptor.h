#pragma once
#include "ObjectType.h"
class CreatureDescriptor
{
private:
	ObjectType objectType;
	size_t numberAppearing;
public:
	CreatureDescriptor(ObjectType, size_t);
	ObjectType GetObjectType() const;
	size_t GetNumberAppearing() const;
};