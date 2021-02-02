#pragma once
#include "DescribedObject.h"
#include "ItemDescriptor.h"
class Item : public DescribedObject<ItemDescriptor>
{
private:
	ObjectType objectType;
public:
	Item(const ItemDescriptor*);
	const ObjectType& GetData() const;
};

