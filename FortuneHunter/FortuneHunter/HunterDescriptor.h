#pragma once
#include <vector>
#include <string>
class HunterDescriptor
{
private:
	std::vector<int> maximumHealths;
	std::vector<int> maximumAttacks;
	std::vector<int> maximumArmors;
	std::string damageSfx;
	std::string deathSfx;
	size_t initialBombs;
public:
	HunterDescriptor();
	void Start(const std::string&);
	int GetMaximumHealth(size_t) const;
	int GetMaximumAttack(size_t) const;
	int GetMaximumArmor(size_t) const;
	const std::string GetDamageSfx() const;
	const std::string GetDeathSfx() const;
	size_t GetInitialBombs() const;
};

