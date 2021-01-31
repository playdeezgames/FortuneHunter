#include "HealthLevelSprites.h"
#include "Utility.h"
HealthLevel HealthLevelSprites::StringToIdentifier(const std::string& value)
{
	return (HealthLevel)tggd::common::Utility::StringToInt(value);
}