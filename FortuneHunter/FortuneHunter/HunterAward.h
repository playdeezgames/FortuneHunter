#pragma once
#include <vector>
#include <string>
enum class HunterAward
{
	DIAMOND,
	HEALTH,
	EXIT_KEY,
	EXIT
};
class HunterAwardHelper
{
public:
	static const std::vector<HunterAward>& GetAll();
	static const std::string& GetName(HunterAward);
};

