#include "FortuneHunterApplication.h"
#include "Constants\Window.h"
#include "Constants\Config.h"
#include "Constants\Color.h"
#include "CommandProcessors\MainMenuCommandProcessor.h"
#include "CommandProcessors\ConfirmQuitCommandProcessor.h"
#include "CommandProcessors\InPlayCommandProcessor.h"
#include "Renderers\MainMenuRenderer.h"
#include "Renderers\ConfirmQuitRenderer.h"
#include "Renderers\InPlayRenderer.h"
#include "Common\Utility.h"
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
	, gameData()
{

}

void FortuneHunterApplication::Start()
{
	tggd::common::Utility::SeedRandomNumberGenerator();

	gameData.Start();
	controllerManager.Start();

	textureManager.Start(GetMainRenderer(), Constants::Config::Files::TEXTURES);
	spriteManager.Start(textureManager, Constants::Config::Files::SPRITES);
	soundManager.Start(Constants::Config::Files::SFX, Constants::Config::Files::MUX);

	commandProcessors.AddCommandProcessor(UIState::MAIN_MENU, new MainMenuCommandProcessor(uiState, mainMenuState, gameData));
	commandProcessors.AddCommandProcessor(UIState::CONFIRM_QUIT, new ConfirmQuitCommandProcessor(uiState, confirmState));
	commandProcessors.AddCommandProcessor(UIState::IN_PLAY, new InPlayCommandProcessor(uiState, gameData));

	renderers.AddRenderer(UIState::MAIN_MENU, new MainMenuRenderer(GetMainRenderer(), romFont, mainMenuState));
	renderers.AddRenderer(UIState::CONFIRM_QUIT, new ConfirmQuitRenderer(GetMainRenderer(), romFont, confirmState));
	renderers.AddRenderer(UIState::IN_PLAY, new InPlayRenderer(GetMainRenderer(), romFont, spriteManager, gameData));
}

void FortuneHunterApplication::Finish()
{
	commandProcessors.Finish();
	soundManager.Finish();
	spriteManager.Finish();
	textureManager.Finish();
	controllerManager.Finish();
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