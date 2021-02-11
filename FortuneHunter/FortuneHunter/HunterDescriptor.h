#pragma once
#include <vector>
#include <string>
#include "json.hpp"
class HunterDescriptor
{
private:
	std::vector<int> maximumHealths;
	std::vector<int> maximumAttacks;
	std::vector<int> maximumArmors;
	std::string damageSfx;
	std::string deathSfx;
	size_t initialBombs;
	std::string bombSfx;
	std::string noBombSfx;
	int bombDamage;
public:
	HunterDescriptor(const nlohmann::json&);
	int GetMaximumHealth(size_t) const;
	int GetMaximumAttack(size_t) const;
	int GetMaximumArmor(size_t) const;
	const std::string GetDamageSfx() const;
	const std::string GetDeathSfx() const;
	const std::string GetBombSfx() const;
	const std::string GetNoBombSfx() const;
	size_t GetInitialBombs() const;
	int GetBombDamage() const;
};

