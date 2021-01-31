#include "FortuneHunterApplication.h"
#include "WindowConstants.h"
#include "ConfigConstants.h"
#include "ColorConstants.h"
#include "MainMenuCommandProcessor.h"
#include "ConfirmQuitCommandProcessor.h"
#include "InPlayCommandProcessor.h"
#include "MainMenuRenderer.h"
#include "ConfirmQuitRenderer.h"
#include "InPlayRenderer.h"
#include "Utility.h"
FortuneHunterApplication FortuneHunterApplication::application;

FortuneHunterApplication::FortuneHunterApplication()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, soundManager()
	, textureManager()
	, uiState(UIState::MAIN_MENU)
	, mainMenuState(MainMenuState::START)
	, renderers(uiState)
	, spriteManager()
	, romFont(spriteManager, Constants::Config::Files::ROMFONT)
	, controllerManager()
	, commandProcessors(uiState)
	, eventHandler(commandProcessors, controllerManager, uiState)
	, confirmState(ConfirmState::NO)
	, creatureDescriptors()
	, gameData(soundManager, creatureDescriptors)
	, statusPanelRenderer(nullptr)
	, terrainSprites()
	, healthLevelSprites()
	, objectSprites()
	, roomPanelRenderer(nullptr)
{

}

void FortuneHunterApplication::Start()
{
	tggd::common::Utility::SeedRandomNumberGenerator();

	creatureDescriptors.Start(Constants::Config::Files::CREATUREDESCRIPTORS);
	gameData.Start();
	controllerManager.Start();

	textureManager.Start(GetMainRenderer(), Constants::Config::Files::TEXTURES);
	spriteManager.Start(textureManager, Constants::Config::Files::SPRITES);
	soundManager.Start(Constants::Config::Files::SFX, Constants::Config::Files::MUX);
	terrainSprites.Start(spriteManager, Constants::Config::Files::TERRAINSPRITES);
	healthLevelSprites.Start(spriteManager, Constants::Config::Files::HEALTHLEVELSPRITES);
	objectSprites.Start(spriteManager, Constants::Config::Files::OBJECTSPRITES);

	commandProcessors.AddCommandProcessor(UIState::MAIN_MENU, new MainMenuCommandProcessor(uiState, mainMenuState, gameData));
	commandProcessors.AddCommandProcessor(UIState::CONFIRM_QUIT, new ConfirmQuitCommandProcessor(uiState, confirmState));
	commandProcessors.AddCommandProcessor(UIState::IN_PLAY, new InPlayCommandProcessor(uiState, gameData));

	statusPanelRenderer = new StatusPanelRenderer(GetMainRenderer(), romFont, gameData);
	roomPanelRenderer = 
		new RoomPanelRenderer
		(
			GetMainRenderer(), 
			romFont, 
			spriteManager, 
			terrainSprites, 
			healthLevelSprites,
			gameData
		);

	renderers.AddRenderer(UIState::MAIN_MENU, new MainMenuRenderer(GetMainRenderer(), romFont, mainMenuState));
	renderers.AddRenderer(UIState::CONFIRM_QUIT, new ConfirmQuitRenderer(GetMainRenderer(), romFont, confirmState));
	renderers.AddRenderer(UIState::IN_PLAY, new InPlayRenderer(GetMainRenderer(), romFont, statusPanelRenderer, roomPanelRenderer, gameData));
}

void FortuneHunterApplication::Finish()
{
	healthLevelSprites.Finish();
	terrainSprites.Finish();
	objectSprites.Finish();
	commandProcessors.Finish();
	soundManager.Finish();
	spriteManager.Finish();
	textureManager.Finish();
	controllerManager.Finish();
	renderers.Finish();
	creatureDescriptors.Finish();
	tggd::common::Utility::SafeDelete(statusPanelRenderer);
	tggd::common::Utility::SafeDelete(roomPanelRenderer);
}

void FortuneHunterApplication::Update(int milliSeconds)
{

}

void FortuneHunterApplication::Draw() const
{
	SDL_RenderClear(GetMainRenderer());
	renderers.Draw();
}

void FortuneHunterApplication::OnEvent(const SDL_Event& evt)
{
	eventHandler.OnEvent(evt);
}

bool FortuneHunterApplication::IsRunning() const
{
	return uiState != UIState::QUIT;
}