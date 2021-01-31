#pragma once
#include "SpriteTable.h"
#include "ObjectType.h"
class ObjectSprites: public tggd::common::SpriteTable<ObjectType>
{
protected:
	ObjectType StringToIdentifier(const std::string&);
};

