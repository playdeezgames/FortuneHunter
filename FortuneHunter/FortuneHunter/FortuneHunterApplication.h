#pragma once
#include "Common\Application.h"
#include "Common\SoundManager.h"
#include "Common\TextureManager.h"
#include "Common\Sprite.h"
class FortuneHunterApplication : public tggd::common::Application
{
private:
	static FortuneHunterApplication application;
	tggd::common::SoundManager soundManager;
	tggd::common::TextureManager textureManager;
protected:
	void Start();
	void Finish();
	void Update(int);
public:
	FortuneHunterApplication();
	void Draw() const;
	bool OnEvent(const SDL_Event&);
};

