#pragma once
#include "Common\Application.h"
#include "Common\Managers\SoundManager.h"
#include "Common\Managers\TextureManager.h"
#include "Common\Graphics\Sprite.h"
#include "Common\Managers\SpriteManager.h"
#include "Common\Managers\RenderManager.h"
#include "Common\Graphics\SpriteFont.h"
#include "UI\UIState.h"
#include "UI\MainMenuState.h"
#include "Common\Managers\ControllerManager.h"
#include "Common\Managers\CommandProcessorManager.h"
#include "CommandProcessors\Command.h"
#include "EventHandlers\FortuneHunterEventHandler.h"
#include "UI\ConfirmState.h"
#include "Game\GameData.h"
#include "Renderers\StatusPanelRenderer.h"
class FortuneHunterApplication : public tggd::common::Application
{
private:
	static FortuneHunterApplication application;
	tggd::common::SoundManager soundManager;
	tggd::common::TextureManager textureManager;
	tggd::common::SpriteManager spriteManager;
	tggd::common::CommandProcessorManager<UIState, Command> commandProcessors;
	tggd::common::RenderManager<UIState> renderers;
	tggd::common::ControllerManager controllerManager;
	tggd::common::SpriteFont romFont;
	StatusPanelRenderer* statusPanelRenderer;

	FortuneHunterEventHandler eventHandler;

	GameData gameData;

	UIState uiState;
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

