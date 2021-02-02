#pragma once
#include <map>
#include "HealthLevel.h"
#include "SpriteTable.h"
class HealthLevelSprites : public tggd::common::SpriteTable<HealthLevel>
{
protected:
	HealthLevel StringToIdentifier(const std::string&);
public:
	HealthLevelSprites(tggd::common::FinishManager&);
};

