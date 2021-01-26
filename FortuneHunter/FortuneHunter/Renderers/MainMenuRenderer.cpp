#include "MainMenuRenderer.h"
#include "..\Constants\Color.h"
#include "..\Constants\UI.h"

MainMenuRenderer::MainMenuRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont, const MainMenuState& mainMenuState)
	: BaseRenderer(renderer, romFont)
	, mainMenuState(mainMenuState)
{

}

void MainMenuRenderer::Draw() const
{
	GetRomFont().WriteText(GetMainRenderer(), 0, 0, "Welcome to Fortune Hunter!", Constants::Color::GREEN);//TODO magic string
	DrawMenuItem(0, "Start", MainMenuState::START);//TODO magic string
	DrawMenuItem(1, "Instructions", MainMenuState::INSTRUCTIONS);//TODO magic string
	DrawMenuItem(2, "About", MainMenuState::ABOUT);//TODO magic string
	DrawMenuItem(3, "Options", MainMenuState::OPTIONS);//TODO magic string
	DrawMenuItem(4, "Quit", MainMenuState::QUIT);//TODO magic string
}

void MainMenuRenderer::DrawMenuItem(int line, const std::string& text, const MainMenuState& state) const
{
	GetRomFont().WriteText
		(
			GetMainRenderer(), 
			0, 
			Constants::UI::MainMenu::OFFSET_Y + Constants::UI::MainMenu::LINE_HEIGHT * line,
			text, 
			(mainMenuState == state) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY)
		);
}


