#include "Options.h"
#include "Utility.h"
#include <io.h>
Options::Options
(
	tggd::common::SoundManager& soundManager, 
	const std::string& fileName
)
	: fileName(fileName)
	, soundManager(soundManager)
{
}

const std::string PROPERTY_MUTED = "muted";
const std::string PROPERTY_SFX_VOLUME = "sfxVolume";
const std::string PROPERTY_MUX_VOLUME = "muxVolume";

void Options::Start()
{
	auto properties = tggd::common::Utility::LoadJSON(fileName);
	soundManager.SetMuted((bool)properties[PROPERTY_MUTED]);
	soundManager.SetSfxVolume((int)properties[PROPERTY_SFX_VOLUME]);
	soundManager.SetMuxVolume((int)properties[PROPERTY_MUX_VOLUME]);
}

void Options::Save()
{
	FILE* output = nullptr;
	if (0 == fopen_s(&output, fileName.c_str(), "w"))
	{
		if (output)
		{
			fprintf
			(
				output, 
				"{\"muted\":%s,\"sfxVolume\":%d,\"muxVolume\":%d}",
				(soundManager.IsMuted()) ? ( "true" ) : ( "false" ),
				soundManager.GetSfxVolume(),
				soundManager.GetMuxVolume()
			);
			fclose(output);
		}
	}
}
