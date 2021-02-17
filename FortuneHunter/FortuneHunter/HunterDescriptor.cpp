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
const std::string PROPERTY_BOMB_DAMAGE = "bombDamage";
const std::string PROPERTY_AWARDS = "awards";
const std::string PROPERTY_NAME = "name";
const std::string PROPERTY_NEXT_DIFFICULTY = "nextDifficulty";


HunterDescriptor::HunterDescriptor(const nlohmann::json& properties)
	: maximumHealths()
	, maximumAttacks()
	, maximumArmors()
	, initialBombs(0)
	, deathSfx("")
	, damageSfx("")
	, bombDamage(0)
{
	auto& maxHealths = properties[PROPERTY_MAXIMUM_HEALTHS];
	for (auto& maxHealth : maxHealths)
	{
		maximumHealths.push_back(maxHealth);
	}
	auto& maxAttacks = properties[PROPERTY_MAXIMUM_ATTACKS];
	for (auto& maxAttack : maxAttacks)
	{
		maximumAttacks.push_back(maxAttack);
	}
	auto& maxArmors = properties[PROPERTY_MAXIMUM_ARMOR];
	for (auto& maxArmor : maxArmors)
	{
		maximumArmors.push_back(maxArmor);
	}
	deathSfx = properties[PROPERTY_DEATH_SFX];
	damageSfx = properties[PROPERTY_DAMAGE_SFX];
	bombSfx = properties[PROPERTY_BOMB_SFX];
	noBombSfx = properties[PROPERTY_NO_BOMB_SFX];
	initialBombs = properties[PROPERTY_INITIAL_BOMBS];
	bombDamage = properties[PROPERTY_BOMB_DAMAGE];
	nextDifficulty = properties[PROPERTY_NEXT_DIFFICULTY];
	name = properties[PROPERTY_NAME];
	auto awardItems = properties[PROPERTY_AWARDS];
	for (auto& item : awardItems.items())
	{
		HunterAward id = (HunterAward)tggd::common::Utility::StringToInt(item.key());
		awards[id] = (int)item.value();
	}
}

static int GetLevel(size_t level, const std::vector<int>& levels)
{
	level = (level < levels.size()) ? (level) : (levels.size() - 1);
	return levels[level];
}

int HunterDescriptor::GetMaximumHealth(size_t level) const
{
	return GetLevel(level, maximumHealths);
}

int HunterDescriptor::GetMaximumAttack(size_t level) const
{
	return GetLevel(level, maximumAttacks);
}

int HunterDescriptor::GetMaximumArmor(size_t level) const
{
	return GetLevel(level, maximumArmors);
}

const std::string& HunterDescriptor::GetDamageSfx() const
{
	return damageSfx;
}

const std::string& HunterDescriptor::GetDeathSfx() const
{
	return deathSfx;
}

size_t HunterDescriptor::GetInitialBombs() const
{
	return initialBombs;
}

const std::string& HunterDescriptor::GetBombSfx() const
{
	return bombSfx;
}

const std::string& HunterDescriptor::GetNoBombSfx() const
{
	return noBombSfx;
}

int HunterDescriptor::GetBombDamage() const
{
	return bombDamage;
}

int HunterDescriptor::GetAward(HunterAward award) const
{
	auto iter = awards.find(award);
	if (iter != awards.end())
	{
		return iter->second;
	}
	return 0;
}

const std::string& HunterDescriptor::GetName() const
{
	return name;
}

int HunterDescriptor::GetNextDifficulty() const
{
	return nextDifficulty;
}
