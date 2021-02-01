#pragma once
#include "BaseDescriptor.h"
class ItemDescriptor : public BaseDescriptor
{
public:
	ItemDescriptor(ObjectType, size_t, const std::set<TerrainType>&);
};

