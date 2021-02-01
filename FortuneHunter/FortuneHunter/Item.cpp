#include "Item.h"
Item::Item(const ItemDescriptor* descriptor)
	: DescribedObject<ItemDescriptor>(descriptor)
	, objectType(descriptor->GetObjectType())
{

}

const ObjectType& Item::GetData() const
{
	return objectType;
}
