#include "HunterDescriptor.h"
#include <string>
#include "json.hpp"
#include "Utility.h"
const std::string PROPERTY_MAXIMUM_HEALTHS = "maximumHealths";
const std::string PROPERTY_MAXIMUM_ATTACKS = "maximumAttacks";
const std::string PROPERTY_MAXIMUM_ARMOR = "maximumArmors";
const std::string PROPERTY_DAMAGE_SFX = "damageSfx";
const std::string PROPERTY_DEATH_SFX = "deathSfx";
const std::string PROPERTY_BOMB_SFX = "bombSfx";
const std::string PROPERTY_NO_BOMB_SFX = "noBombSfx";
const std::string PROPERTY_INITIAL_BOMBS = "initialBombs";

HunterDescriptor::HunterDescriptor()
	: maximumHealths()
	, maximumAttacks()
	, maximumArmors()
	, initialBombs(0)
	, deathSfx("")
	, damageSfx("")
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
	deathSfx = j[PROPERTY_DEATH_SFX];
	damageSfx = j[PROPERTY_DAMAGE_SFX];
	bombSfx = j[PROPERTY_BOMB_SFX];
	noBombSfx = j[PROPERTY_NO_BOMB_SFX];
	initialBombs = j[PROPERTY_INITIAL_BOMBS];
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

const std::string HunterDescriptor::GetDamageSfx() const
{
	return damageSfx;
}

const std::string HunterDescriptor::GetDeathSfx() const
{
	return deathSfx;
}

size_t HunterDescriptor::GetInitialBombs() const
{
	return initialBombs;
}

const std::string HunterDescriptor::GetBombSfx() const
{
	return bombSfx;
}

const std::string HunterDescriptor::GetNoBombSfx() const
{
	return noBombSfx;
}
