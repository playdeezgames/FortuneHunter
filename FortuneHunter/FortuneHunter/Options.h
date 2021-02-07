#pragma once
#include <string>
#include "SoundManager.h"
class Options
{
private:
	std::string fileName;
	tggd::common::SoundManager& soundManager;
public:
	Options(tggd::common::SoundManager&, const std::string&);
	void Start();
	void Save() const;
};