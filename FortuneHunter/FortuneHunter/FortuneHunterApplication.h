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
#include "TerrainSprites.h"
#include "CreatureDescriptorManager.h"
#include "HealthLevelSprites.h"
#include "ObjectSprites.h"
#include "ItemDescriptorManager.h"
#include "FinishManager.h"
#include "HunterDescriptor.h"
#include "Options.h"
#include "OptionsState.h"
#include "HunterDescriptorManager.h"
#include "Statistics.h"
#include "ColorManager.h"
class FortuneHunterApplication : public tggd::common::Application
{
private:
	static FortuneHunterApplication application;

	tggd::common::FinishManager finishManager;

	tggd::common::SoundManager soundManager;
	Options options;
	tggd::common::TextureManager textureManager;
	tggd::common::SpriteManager spriteManager;
	tggd::common::SpriteFont romFont;
	tggd::common::ColorManager colorManager;

	tggd::common::CommandProcessorManager<UIState, Command> commandProcessors;
	FortuneHunterEventHandler eventHandler;
	tggd::common::ControllerManager controllerManager;

	tggd::common::RenderManager<UIState> renderers;
	StatusPanelRenderer* statusPanelRenderer;
	RoomPanelRenderer* roomPanelRenderer;
	UIState uiState;
	MainMenuState mainMenuState;
	ConfirmState confirmState;
	OptionsState optionsState;
	Statistics statistics;

	CreatureDescriptorManager creatureDescriptors;
	ItemDescriptorManager itemDescriptors;
	HunterDescriptorManager hunterDescriptors;
	GameData gameData;

	TerrainSprites terrainSprites;
	HealthLevelSprites healthLevelSprites;
	ObjectSprites objectSprites;

	void InitializeDescriptors();
	void InitializeAssetManagers();
	void InitializeSpriteTables();
	void AddCommandProcessors();
	void AddRenderers();
protected:
	void Start();
	void Finish();
	bool IsRunning() const;
public:
	FortuneHunterApplication();
	void Draw() const;
	void OnEvent(const SDL_Event&);
};