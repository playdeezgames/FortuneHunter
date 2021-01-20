#include "SoundManager.h"
namespace tggd::common
{
	const int ANY_CHANNEL = -1;
	const int NO_LOOPS = 0;
	const int LOOP_FOREVER = -1;

	void SoundManager::FinishMusic()
	{
		Mix_HaltMusic();
		for (auto& entry : music)
		{
			if (entry.second)
			{
				Mix_FreeMusic(entry.second);
				entry.second = nullptr;
			}
		}
		music.clear();
	}

	void SoundManager::FinishSound()
	{
		for (auto& entry : sounds)
		{
			if (entry.second)
			{
				Mix_FreeChunk(entry.second);
				entry.second = nullptr;
			}
		}
		sounds.clear();
	}

	void SoundManager::Finish()
	{
		FinishMusic();
		FinishSound();
	}

	void SoundManager::AddSound(const std::string& name, const std::string& filename)
	{
		sounds[name] = Mix_LoadWAV(filename.c_str());
	}

	void SoundManager::AddMusic(const std::string& name, const std::string& filename)
	{
		music[name] = Mix_LoadMUS(filename.c_str());
	}

	void SoundManager::PlaySound(const std::string& name) const
	{
		if (!muted)
		{
			const auto& item = sounds.find(name);
			Mix_PlayChannel(ANY_CHANNEL, item->second , NO_LOOPS);
		}
	}

	void SoundManager::PlayMusic(const std::string& name) const
	{
		if (!muted)
		{
			const auto& item = music.find(name);
			Mix_PlayMusic(item->second, LOOP_FOREVER);
		}
	}

	void SoundManager::SetMuted(bool newValue)
	{
		muted = newValue;
		if (muted)
		{
			Mix_PauseMusic();
		}
		else
		{
			Mix_ResumeMusic();
		}
	}

	bool SoundManager::IsMuted() const
	{
		return muted;
	}

	void SoundManager::SetSfxVolume(int volume)
	{
		sfxVolume = volume;
		for (auto& entry : sounds)
		{
			Mix_VolumeChunk(entry.second, sfxVolume);
		}
	}

	void SoundManager::SetMuxVolume(int volume)
	{
		muxVolume = volume;
		Mix_VolumeMusic(muxVolume);
	}

	int SoundManager::GetSfxVolume() const
	{
		return sfxVolume;
	}

	int SoundManager::GetMuxVolume() const
	{
		return muxVolume;
	}

	SoundManager::SoundManager()
		: muted(false)
		, sfxVolume(MIX_MAX_VOLUME)
		, muxVolume(MIX_MAX_VOLUME)
	{
	}
}

