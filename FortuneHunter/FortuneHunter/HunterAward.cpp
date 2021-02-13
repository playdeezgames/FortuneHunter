#include "HunterAward.h"
static std::vector<HunterAward> allAwards = {HunterAward::DIAMOND, HunterAward::HEALTH, HunterAward::EXIT_KEY, HunterAward::EXIT};

const std::vector<HunterAward>& HunterAwardHelper::GetAll()
{
	return allAwards;
}

static std::vector<std::string> allNames = { "Diamonds", "Health", "Exit Key", "Exited" };

const std::string& HunterAwardHelper::GetName(HunterAward award)
{
	return allNames[(int)award];
}