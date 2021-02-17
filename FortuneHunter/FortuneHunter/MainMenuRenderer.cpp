#include "MainMenuRenderer.h"
#include "ColorConstants.h"
#include "MainMenuConstants.h"

MainMenuRenderer::MainMenuRenderer
(
	SDL_Renderer* renderer, 
	const tggd::common::SpriteFont& romFont, 
	const tggd::common::Sprite* background,
	const MainMenuState& mainMenuState, 
	const GameData& gameData,
	const HunterDescriptorManager& hunterDescriptors
)
	: BaseMenuRenderer(renderer, romFont, background)
	, mainMenuState(mainMenuState)
	, gameData(gameData)
	, hunterDescriptors(hunterDescriptors)
{

}

void MainMenuRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(Constants::UI::MainMenu::TITLE_OFFSET_X + Constants::UI::DROP_SHADOW_X, Constants::UI::DROP_SHADOW_Y + Constants::UI::MainMenu::TITLE_OFFSET_Y), Constants::UI::MainMenu::TITLE, Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(Constants::UI::MainMenu::TITLE_OFFSET_X, Constants::UI::MainMenu::TITLE_OFFSET_Y), Constants::UI::MainMenu::TITLE, Constants::Color::LIGHT_GREEN);
	if (gameData.CanContinue())
	{
		DrawMenuItem(0, Constants::UI::MainMenu::OPTION_CONTINUE, MainMenuState::START);
	}
	else
	{
		DrawMenuItem(0, Constants::UI::MainMenu::OPTION_START, MainMenuState::START);
	}
	auto hunterDescriptor = hunterDescriptors.GetDescriptor(gameData.GetDifficulty());
	DrawMenuItem(1, hunterDescriptor->GetName(), MainMenuState::DIFFICULTY);
	DrawMenuItem(2, Constants::UI::MainMenu::OPTION_INSTRUCTIONS, MainMenuState::INSTRUCTIONS);
	DrawMenuItem(3, Constants::UI::MainMenu::OPTION_STATISTICS, MainMenuState::STATISTICS);
	DrawMenuItem(4, Constants::UI::MainMenu::OPTION_ABOUT, MainMenuState::ABOUT);
	DrawMenuItem(5, Constants::UI::MainMenu::OPTION_OPTIONS, MainMenuState::OPTIONS);
	DrawMenuItem(6, Constants::UI::MainMenu::OPTION_QUIT, MainMenuState::QUIT);
}

void MainMenuRenderer::DrawMenuItem(int line, const std::string& text, const MainMenuState& state) const
{
	GetFont().WriteTextCentered
	(
		GetRenderer(),
		tggd::common::XY<int>(Constants::UI::DROP_SHADOW_X + Constants::UI::MainMenu::MENU_OFFSET_X,
			Constants::UI::MainMenu::MENU_OFFSET_Y + Constants::UI::MainMenu::LINE_HEIGHT * line + Constants::UI::DROP_SHADOW_Y),
		text,
		(Constants::Color::BLACK)
	);
	GetFont().WriteTextCentered
		(
			GetRenderer(), 
			tggd::common::XY<int>(Constants::UI::MainMenu::MENU_OFFSET_X,
			Constants::UI::MainMenu::MENU_OFFSET_Y + Constants::UI::MainMenu::LINE_HEIGHT * line),
			text, 
			(mainMenuState == state) ? (Constants::Color::YELLOW) : (Constants::Color::WHITE)
		);
}


