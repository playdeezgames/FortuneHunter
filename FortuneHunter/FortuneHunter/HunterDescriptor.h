#pragma once
#include <vector>
#include <string>
class HunterDescriptor
{
private:
	std::vector<int> maximumHealths;
	std::vector<int> maximumAttacks;
	std::vector<int> maximumArmors;
public:
	HunterDescriptor();
	void Start(const std::string&);
	int GetMaximumHealth(size_t) const;
	int GetMaximumAttack(size_t) const;
	int GetMaximumArmor(size_t) const;
};

