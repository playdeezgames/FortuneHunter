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
#include "OptionsCommandProcessor.h"
#include "OptionsRenderer.h"
#include "AboutCommandProcessor.h"
#include "InstructionsCommandProcessor.h"
#include "AboutRenderer.h"
#include "InstructionsRenderer.h"
#include "BackgroundConstants.h"

FortuneHunterApplication FortuneHunterApplication::application;

FortuneHunterApplication::FortuneHunterApplication()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, finishManager()
	, soundManager(finishManager)
	, options(soundManager, Constants::Config::Files::OPTIONS)
	, textureManager(finishManager)
	, uiState(UIState::MAIN_MENU)
	, mainMenuState(MainMenuState::START)
	, renderers(uiState, finishManager)
	, spriteManager(finishManager)
	, romFont(spriteManager, Constants::Config::Files::ROMFONT)
	, controllerManager(finishManager)
	, commandProcessors(uiState, finishManager)
	, eventHandler(commandProcessors, controllerManager, uiState)
	, confirmState(ConfirmState::NO)
	, creatureDescriptors(finishManager)
	, itemDescriptors(finishManager)
	, hunterDescriptors(finishManager)
	, gameData(soundManager, creatureDescriptors, itemDescriptors, hunterDescriptors)
	, statusPanelRenderer(nullptr)
	, terrainSprites(finishManager)
	, healthLevelSprites(finishManager)
	, objectSprites(finishManager)
	, roomPanelRenderer(nullptr)
	, optionsState(OptionsState::BACK)
{

}

void FortuneHunterApplication::AddRenderers()
{
	statusPanelRenderer = new StatusPanelRenderer(GetMainRenderer(), romFont, spriteManager, gameData);
	roomPanelRenderer =
		new RoomPanelRenderer
		(
			GetMainRenderer(),
			romFont,
			spriteManager,
			terrainSprites,
			healthLevelSprites,
			objectSprites,
			gameData
		);
	renderers.AddRenderer
	(
		UIState::MAIN_MENU,
		new MainMenuRenderer
		(
			GetMainRenderer(),
			romFont,
			spriteManager.GetSprite(Constants::UI::Backgrounds::MAIN_MENU),
			mainMenuState,
			gameData
		)
	);
	renderers.AddRenderer
	(
		UIState::CONFIRM_QUIT, 
		new ConfirmQuitRenderer
		(
			GetMainRenderer(), 
			romFont, 
			spriteManager.GetSprite(Constants::UI::Backgrounds::CONFIRM_QUIT),
			confirmState
		)
	);
	renderers.AddRenderer
	(
		UIState::IN_PLAY, 
		new InPlayRenderer
		(
			GetMainRenderer(), 
			romFont, 
			spriteManager.GetSprite(Constants::UI::Backgrounds::IN_PLAY),
			statusPanelRenderer, 
			roomPanelRenderer, 
			gameData
		)
	);
	renderers.AddRenderer
	(
		UIState::OPTIONS, 
		new OptionsRenderer
		(
			GetMainRenderer(), 
			romFont, 
			spriteManager.GetSprite(Constants::UI::Backgrounds::OPTIONS),
			soundManager, 
			optionsState
		)
	);
	renderers.AddRenderer
	(
		UIState::ABOUT,
		new AboutRenderer
		(
			GetMainRenderer(),
			romFont,
			spriteManager.GetSprite(Constants::UI::Backgrounds::ABOUT)
		)
	);
	renderers.AddRenderer
	(
		UIState::INSTRUCTIONS,
		new InstructionsRenderer
		(
			GetMainRenderer(),
			romFont,
			spriteManager.GetSprite(Constants::UI::Backgrounds::INSTRUCTIONS)
		)
	);
}

void FortuneHunterApplication::InitializeDescriptors()
{
	creatureDescriptors.Start(Constants::Config::Files::CREATUREDESCRIPTORS);
	itemDescriptors.Start(Constants::Config::Files::ITEMDESCRIPTORS);
	hunterDescriptors.Start(Constants::Config::Files::HUNTERDESCRIPTORS);
}

void FortuneHunterApplication::InitializeAssetManagers()
{
	textureManager.Start(GetMainRenderer(), Constants::Config::Files::TEXTURES);
	spriteManager.Start(textureManager, Constants::Config::Files::SPRITES);
	soundManager.Start(Constants::Config::Files::SFX, Constants::Config::Files::MUX);
}

void FortuneHunterApplication::InitializeSpriteTables()
{
	terrainSprites.Start(spriteManager, Constants::Config::Files::TERRAINSPRITES);
	healthLevelSprites.Start(spriteManager, Constants::Config::Files::HEALTHLEVELSPRITES);
	objectSprites.Start(spriteManager, Constants::Config::Files::OBJECTSPRITES);
}

void FortuneHunterApplication::AddCommandProcessors()
{
	commandProcessors.AddCommandProcessor(UIState::MAIN_MENU, new MainMenuCommandProcessor(uiState, mainMenuState, gameData));
	commandProcessors.AddCommandProcessor(UIState::CONFIRM_QUIT, new ConfirmQuitCommandProcessor(uiState, confirmState));
	commandProcessors.AddCommandProcessor(UIState::IN_PLAY, new InPlayCommandProcessor(uiState, gameData));
	commandProcessors.AddCommandProcessor(UIState::OPTIONS, new OptionsCommandProcessor(uiState, optionsState, soundManager, options));
	commandProcessors.AddCommandProcessor(UIState::ABOUT, new AboutCommandProcessor(uiState));
	commandProcessors.AddCommandProcessor(UIState::INSTRUCTIONS, new InstructionsCommandProcessor(uiState));
}

void FortuneHunterApplication::Start()
{
	tggd::common::Utility::SeedRandomNumberGenerator();
	InitializeDescriptors();
	controllerManager.Start();
	InitializeAssetManagers();
	options.Start();//this has to happen AFTER the asset managers are set up!
	InitializeSpriteTables();
	AddCommandProcessors();
	AddRenderers();
}

void FortuneHunterApplication::Finish()
{
	finishManager.Finish();
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