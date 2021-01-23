#include "FortuneHunterApplication.h"
#include "Constants\Window.h"
#include "Constants\Config.h"
#include "Constants\Color.h"
#include "CommandProcessors\MainMenuCommandProcessor.h"
#include "CommandProcessors\ConfirmQuitCommandProcessor.h"
#include "Renderers\ConfirmQuitRenderer.h"
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
{

}

void FortuneHunterApplication::Start()
{
	controllerManager.Start();

	textureManager.Start(GetMainRenderer(), Constants::Config::Files::TEXTURES);
	spriteManager.Start(textureManager, Constants::Config::Files::SPRITES);
	soundManager.Start(Constants::Config::Files::SFX, Constants::Config::Files::MUX);

	commandProcessors.AddCommandProcessor(UIState::MAIN_MENU, new MainMenuCommandProcessor(uiState, mainMenuState));
	commandProcessors.AddCommandProcessor(UIState::CONFIRM_QUIT, new ConfirmQuitCommandProcessor(uiState, confirmState));

	renderers.AddRenderer(UIState::MAIN_MENU, new MainMenuRenderer(GetMainRenderer(), romFont, mainMenuState));
	renderers.AddRenderer(UIState::CONFIRM_QUIT, new ConfirmQuitRenderer(GetMainRenderer(), romFont, confirmState));
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