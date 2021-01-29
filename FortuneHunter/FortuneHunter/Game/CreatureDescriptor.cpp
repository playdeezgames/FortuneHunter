#include "CreatureDescriptor.h"
CreatureDescriptor::CreatureDescriptor(ObjectType objectType)
	: objectType(objectType)
{

}

ObjectType CreatureDescriptor::GetObjectType() const
{
	return objectType;
}
