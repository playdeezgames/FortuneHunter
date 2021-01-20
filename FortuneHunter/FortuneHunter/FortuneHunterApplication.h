#pragma once
#include "Common\Application.h"
#include "Common\SoundManager.h"
class FortuneHunterApplication : public tggd::common::Application
{
private:
	static FortuneHunterApplication application;
	tggd::common::SoundManager soundManager;
protected:
	void Start();
	void Finish();
	void Update(int);
public:
	FortuneHunterApplication();
	void Draw() const;
	bool OnEvent(const SDL_Event&);
};

