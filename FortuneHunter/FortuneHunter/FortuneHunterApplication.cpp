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
#include "FinalScoreCommandProcessor.h"
#include "StatisticsCommandProcessor.h"
#include "FinalScoreRenderer.h"
#include "StatisticsRenderer.h"
#include "UIConstants.h"

FortuneHunterApplication FortuneHunterApplication::application;

FortuneHunterApplication::FortuneHunterApplication()
	: Application
	(
		Constants::Window::WIDTH, 
		Constants::Window::HEIGHT, 
		Constants::Window::TITLE, 
		Constants::Config::Files::ICON
	)
	, finishManager()
	, colorManager(finishManager)
	, soundManager(finishManager)
	, textureManager(finishManager)
	, uiState(UIState::MAIN_MENU)
	, mainMenuState(MainMenuState::START)
	, renderers(uiState, finishManager)
	, spriteManager(finishManager)
	, romFont(spriteManager, colorManager, Constants::Config::Files::ROMFONT)
	, controllerManager(finishManager)
	, commandProcessors(uiState, finishManager)
	, eventHandler(commandProcessors, controllerManager, uiState)
	, confirmState(ConfirmState::NO)
	, creatureDescriptors(finishManager)
	, itemDescriptors(finishManager)
	, hunterDescriptors(finishManager)
	, gameData(soundManager, creatureDescriptors, itemDescriptors, hunterDescriptors)
	, options(soundManager, gameData, Constants::Config::Files::OPTIONS)
	, statusPanelRenderer(nullptr)
	, terrainSprites(finishManager)
	, healthLevelSprites(finishManager)
	, objectSprites(finishManager)
	, roomPanelRenderer(nullptr)
	, optionsState(OptionsState::BACK)
	, statistics(Constants::Config::Files::STATISTICS)
	, helpPages(finishManager, romFont)
	, helpPage("first") //TODO: magic string
{

}

void FortuneHunterApplication::AddRenderers()
{
	statusPanelRenderer = new StatusPanelRenderer(GetRenderer(), romFont, spriteManager, gameData);
	roomPanelRenderer =
		new RoomPanelRenderer
		(
			GetRenderer(),
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
			GetRenderer(),
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
			GetRenderer(),
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
			GetRenderer(),
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
			GetRenderer(),
			romFont, 
			spriteManager.GetSprite(Constants::UI::Backgrounds::OPTIONS),
			soundManager, 
			optionsState
		)
	);
	renderers.AddRenderer
	(
		UIState::FINAL_SCORE,
		new FinalScoreRenderer
		(
			GetRenderer(),
			romFont,
			spriteManager.GetSprite(Constants::UI::Backgrounds::FINAL_SCORE),
			gameData
		)
	);
	renderers.AddRenderer
	(
		UIState::STATISTICS,
		new StatisticsRenderer
		(
			GetRenderer(),
			romFont,
			spriteManager.GetSprite(Constants::UI::Backgrounds::STATISTICS),
			statistics
		)
	);
	renderers.AddRenderer
	(
		UIState::ABOUT,
		new AboutRenderer
		(
			GetRenderer(),
			romFont,
			spriteManager.GetSprite(Constants::UI::Backgrounds::ABOUT)
		)
	);
	renderers.AddRenderer
	(
		UIState::INSTRUCTIONS,
		new InstructionsRenderer
		(
			GetRenderer(),
			romFont,
			spriteManager.GetSprite(Constants::UI::Backgrounds::INSTRUCTIONS),
			helpPages,
			helpPage
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
	textureManager.Start(GetRenderer(), Constants::Config::Files::TEXTURES);
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
	commandProcessors.AddCommandProcessor(UIState::IN_PLAY, new InPlayCommandProcessor(uiState, gameData, statistics));
	commandProcessors.AddCommandProcessor(UIState::OPTIONS, new OptionsCommandProcessor(uiState, optionsState, soundManager, options));
	commandProcessors.AddCommandProcessor(UIState::ABOUT, new AboutCommandProcessor(uiState));
	commandProcessors.AddCommandProcessor(UIState::INSTRUCTIONS, new InstructionsCommandProcessor(uiState, helpPages, helpPage));
	commandProcessors.AddCommandProcessor(UIState::FINAL_SCORE, new FinalScoreCommandProcessor(uiState));
	commandProcessors.AddCommandProcessor(UIState::STATISTICS, new StatisticsCommandProcessor(uiState));
}

void FortuneHunterApplication::Start()
{
	colorManager.Start(Constants::Config::Files::COLORS);
	tggd::common::Utility::SeedRandomNumberGenerator();
	InitializeDescriptors();
	controllerManager.Start();
	InitializeAssetManagers();
	options.Start();//this has to happen AFTER the asset managers are set up!
	InitializeSpriteTables();
	AddCommandProcessors();
	AddRenderers();
	statistics.Load();
	helpPages.Start(Constants::Config::Files::HELP_PAGES);
}

void FortuneHunterApplication::Finish()
{
	finishManager.Finish();
	tggd::common::Utility::SafeDelete(statusPanelRenderer);
	tggd::common::Utility::SafeDelete(roomPanelRenderer);
}

void FortuneHunterApplication::Draw() const
{
	SDL_RenderClear(GetRenderer());
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