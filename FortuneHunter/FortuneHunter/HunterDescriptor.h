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
public:
	HunterDescriptor();
	void Start(const std::string&);
	int GetMaximumHealth(size_t) const;
	int GetMaximumAttack(size_t) const;
	int GetMaximumArmor(size_t) const;
	const std::string GetDamageSfx() const;
	const std::string GetDeathSfx() const;
};

