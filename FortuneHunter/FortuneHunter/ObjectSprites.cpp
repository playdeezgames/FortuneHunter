#include "ObjectSprites.h"
ObjectType ObjectSprites::StringToIdentifier(const std::string& value)
{
	return (ObjectType)tggd::common::Utility::StringToInt(value);
}