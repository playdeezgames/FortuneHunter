#pragma once
#include "Common\Application.h"
#include "Common\SoundManager.h"
#include "Common\TextureManager.h"
#include "Common\Sprite.h"
#include "Common\SpriteManager.h"
#include "Common\EventHandlerManager.h"
#include "Common\RenderManager.h"
#include "Common\SpriteFont.h"
#include "Game\GameState.h"
#include "Game\MainMenuState.h"
#include "EventHandlers\MainMenuEventHandler.h"
#include "Renderers\MainMenuRenderer.h"
#include "Common\ControllerManager.h"
class FortuneHunterApplication : public tggd::common::Application
{
private:
	static FortuneHunterApplication application;
	tggd::common::SoundManager soundManager;
	tggd::common::TextureManager textureManager;
	tggd::common::SpriteManager spriteManager;
	tggd::common::EventHandlerManager<GameState> eventHandlers;
	tggd::common::RenderManager<GameState> renderers;
	tggd::common::ControllerManager controllerManager;
	tggd::common::SpriteFont romFont;
	GameState gameState;
	MainMenuState mainMenuState;
protected:
	void Start();
	void Finish();
	void Update(int);
public:
	FortuneHunterApplication();
	void Draw() const;
	bool OnEvent(const SDL_Event&);
};

