#include "HunterDescriptor.h"
#include <string>
#include "json.hpp"
#include "Utility.h"
const std::string PROPERTY_MAXIMUM_HEALTHS = "maximumHealths";
const std::string PROPERTY_MAXIMUM_ATTACKS = "maximumAttacks";
const std::string PROPERTY_MAXIMUM_ARMOR = "maximumArmors";
HunterDescriptor::HunterDescriptor()
	: maximumHealths()
	, maximumAttacks()
	, maximumArmors()
{

}

void HunterDescriptor::Start(const std::string& fileName)
{
	nlohmann::json j = tggd::common::Utility::LoadJSON(fileName);
	auto& maxHealths = j[PROPERTY_MAXIMUM_HEALTHS];
	for (auto& maxHealth : maxHealths)
	{
		maximumHealths.push_back(maxHealth);
	}
	auto& maxAttacks = j[PROPERTY_MAXIMUM_ATTACKS];
	for (auto& maxAttack : maxAttacks)
	{
		maximumAttacks.push_back(maxAttack);
	}
	auto& maxArmors = j[PROPERTY_MAXIMUM_ARMOR];
	for (auto& maxArmor : maxArmors)
	{
		maximumArmors.push_back(maxArmor);
	}
}

int HunterDescriptor::GetMaximumHealth(size_t level) const
{
	level = (level < maximumHealths.size()) ? (level) : (maximumHealths.size() - 1);
	return maximumHealths[level];
}

int HunterDescriptor::GetMaximumAttack(size_t level) const
{
	level = (level < maximumAttacks.size()) ? (level) : (maximumAttacks.size() - 1);
	return maximumAttacks[level];

}

int HunterDescriptor::GetMaximumArmor(size_t level) const
{
	level = (level < maximumArmors.size()) ? (level) : (maximumArmors.size() - 1);
	return maximumArmors[level];
}


