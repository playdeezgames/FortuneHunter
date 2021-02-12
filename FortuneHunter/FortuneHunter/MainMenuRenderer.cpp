#include "MainMenuRenderer.h"
#include "ColorConstants.h"
#include "MainMenuConstants.h"

MainMenuRenderer::MainMenuRenderer
(
	SDL_Renderer* renderer, 
	const tggd::common::SpriteFont& romFont, 
	const MainMenuState& mainMenuState, 
	const GameData& gameData
)
	: BaseRenderer(renderer, romFont)
	, mainMenuState(mainMenuState)
	, gameData(gameData)
{

}

void MainMenuRenderer::Draw() const
{
	GetRomFont().WriteText(GetMainRenderer(), tggd::common::XY<int>(0, 0), Constants::UI::MainMenu::TITLE, Constants::Color::GREEN);
	if (gameData.CanContinue())
	{
		DrawMenuItem(0, Constants::UI::MainMenu::OPTION_CONTINUE, MainMenuState::START);
	}
	else
	{
		DrawMenuItem(0, Constants::UI::MainMenu::OPTION_START, MainMenuState::START);
	}
	DrawMenuItem(1, Constants::UI::MainMenu::OPTION_INSTRUCTIONS, MainMenuState::INSTRUCTIONS);
	DrawMenuItem(2, Constants::UI::MainMenu::OPTION_ABOUT, MainMenuState::ABOUT);
	DrawMenuItem(3, Constants::UI::MainMenu::OPTION_OPTIONS, MainMenuState::OPTIONS);
	DrawMenuItem(4, Constants::UI::MainMenu::OPTION_QUIT, MainMenuState::QUIT);
}

void MainMenuRenderer::DrawMenuItem(int line, const std::string& text, const MainMenuState& state) const
{
	GetRomFont().WriteText
		(
			GetMainRenderer(), 
			tggd::common::XY<int>(0,
			Constants::UI::MainMenu::OFFSET_Y + Constants::UI::MainMenu::LINE_HEIGHT * line),
			text, 
			(mainMenuState == state) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY)
		);
}


