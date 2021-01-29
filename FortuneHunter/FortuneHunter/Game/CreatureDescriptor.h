#pragma once
#include "ObjectType.h"
class CreatureDescriptor
{
private:
	ObjectType objectType;
public:
	CreatureDescriptor(ObjectType);
	ObjectType GetObjectType() const;
};