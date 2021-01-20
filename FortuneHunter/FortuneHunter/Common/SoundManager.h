#pragma once
#include <map>
#include <string>
#include <SDL_Mixer.h>
namespace tggd::common
{
	class SoundManager
	{
	private:
		std::map<std::string, Mix_Chunk*> sounds;
		int sfxVolume;

		std::map<std::string, Mix_Music*> music;
		int muxVolume;

		bool muted;

		void FinishSound();
		void FinishMusic();
		void AddSound(const std::string&, const std::string&);
		void AddMusic(const std::string&, const std::string&);
	public:
		SoundManager();

		void Start(const std::string&, const std::string&);
		void Finish();

		void PlaySound(const std::string&) const;
		void SetSfxVolume(int);
		int GetSfxVolume() const;

		void PlayMusic(const std::string&) const;
		void SetMuxVolume(int);
		int GetMuxVolume() const;

		void SetMuted(bool);
		bool IsMuted() const;
	};
}
