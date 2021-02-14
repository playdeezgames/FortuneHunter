#include "Options.h"
#include "Utility.h"
#include <io.h>
Options::Options
(
	tggd::common::SoundManager& soundManager, 
	GameData& gameData,
	const std::string& fileName
)
	: fileName(fileName)
	, soundManager(soundManager)
	, gameData(gameData)
{
}

const std::string PROPERTY_MUTED = "muted";
const std::string PROPERTY_SFX_VOLUME = "sfxVolume";
const std::string PROPERTY_MUX_VOLUME = "muxVolume";
const std::string PROPERTY_DIFFICULTY = "difficulty";

void Options::Start()
{
	auto properties = tggd::common::Utility::LoadJSON(fileName);
	gameData.SetDifficulty((int)properties[PROPERTY_DIFFICULTY]);
	soundManager.SetMuted((bool)properties[PROPERTY_MUTED]);
	soundManager.SetSfxVolume((int)properties[PROPERTY_SFX_VOLUME]);
	soundManager.SetMuxVolume((int)properties[PROPERTY_MUX_VOLUME]);
}

void Options::Save() const
{
	nlohmann::json properties;
	properties[PROPERTY_DIFFICULTY] = gameData.GetDifficulty();
	properties[PROPERTY_MUTED] = soundManager.IsMuted();
	properties[PROPERTY_MUX_VOLUME] = soundManager.GetMuxVolume();
	properties[PROPERTY_SFX_VOLUME] = soundManager.GetSfxVolume();
	tggd::common::Utility::SaveJSON(fileName, properties);
}
