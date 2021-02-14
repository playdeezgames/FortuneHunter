#pragma once
#include <string>
#include "SoundManager.h"
#include "GameData.h"
class Options
{
private:
	std::string fileName;
	tggd::common::SoundManager& soundManager;
	GameData& gameData;
public:
	Options(tggd::common::SoundManager&, GameData&, const std::string&);
	void Start();
	void Save() const;
};