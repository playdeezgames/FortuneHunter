#pragma once
#include "Common\Application.h"
#include "Common\SoundManager.h"
#include "Common\TextureManager.h"
#include "Common\Sprite.h"
#include "Common\SpriteManager.h"
#include "Common\RenderManager.h"
#include "Common\SpriteFont.h"
#include "Game\GameState.h"
#include "Game\MainMenuState.h"
#include "Renderers\MainMenuRenderer.h"
#include "Common\ControllerManager.h"
#include "Common\CommandProcessorManager.h"
#include "Game\Command.h"
#include "EventHandlers\FortuneHunterEventHandler.h"
#include "Game\ConfirmState.h"
class FortuneHunterApplication : public tggd::common::Application
{
private:
	static FortuneHunterApplication application;
	tggd::common::SoundManager soundManager;
	tggd::common::TextureManager textureManager;
	tggd::common::SpriteManager spriteManager;
	tggd::common::CommandProcessorManager<GameState, Command> commandProcessors;
	tggd::common::RenderManager<GameState> renderers;
	tggd::common::ControllerManager controllerManager;
	tggd::common::SpriteFont romFont;

	FortuneHunterEventHandler eventHandler;

	GameState gameState;
	MainMenuState mainMenuState;
	ConfirmState confirmState;
protected:
	void Start();
	void Finish();
	void Update(int);
	bool IsRunning() const;
public:
	FortuneHunterApplication();
	void Draw() const;
	void OnEvent(const SDL_Event&);
};

