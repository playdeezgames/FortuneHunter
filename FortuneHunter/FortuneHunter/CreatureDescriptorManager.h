#pragma once
#include "CreatureDescriptor.h"
#include "CreatureType.h"
#include <string>
#include <map>
#include <vector>
class CreatureDescriptorManager
{
private:
	std::map<CreatureType, CreatureDescriptor*> creatureDescriptors;
public:
	CreatureDescriptorManager();
	void Start(const std::string&);
	void Finish();
	std::vector<CreatureType> GetCreatureTypes() const;
	const CreatureDescriptor* GetDescriptor(CreatureType) const;
};
