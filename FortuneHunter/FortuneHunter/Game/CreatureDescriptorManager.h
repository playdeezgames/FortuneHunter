#pragma once
#include "CreatureDescriptor.h"
#include "CreatureType.h"
#include <string>
#include <map>
class CreatureDescriptorManager
{
private:
	std::map<CreatureType, CreatureDescriptor*> creatureDescriptors;
public:
	CreatureDescriptorManager();
	void Start(const std::string&);
	void Finish();
};
