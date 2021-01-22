#include "MainMenuRenderer.h"
#include "..\Constants\Color.h"
MainMenuRenderer::MainMenuRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont, const MainMenuState& mainMenuState)
	: BaseRenderer(renderer, romFont)
	, mainMenuState(mainMenuState)
{

}

void MainMenuRenderer::Draw() const
{
	GetRomFont().WriteText(GetMainRenderer(), 0, 0, "Start", (mainMenuState == MainMenuState::START) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY));
	GetRomFont().WriteText(GetMainRenderer(), 0, 16, "Quit", (mainMenuState == MainMenuState::QUIT) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY));
}

