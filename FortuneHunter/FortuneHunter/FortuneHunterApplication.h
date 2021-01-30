#pragma once
#include "Application.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "RenderManager.h"
#include "SpriteFont.h"
#include "UIState.h"
#include "MainMenuState.h"
#include "ControllerManager.h"
#include "CommandProcessorManager.h"
#include "Command.h"
#include "FortuneHunterEventHandler.h"
#include "ConfirmState.h"
#include "GameData.h"
#include "StatusPanelRenderer.h"
#include "RoomPanelRenderer.h"
#include "TerrainSpriteManager.h"
#include "CreatureDescriptorManager.h"
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
	CreatureDescriptorManager creatureDescriptors;
	TerrainSpriteManager terrainSprites;
	StatusPanelRenderer* statusPanelRenderer;
	RoomPanelRenderer* roomPanelRenderer;

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

