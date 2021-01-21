#include "MainMenuRenderer.h"
#include "..\Constants\Color.h"
SDL_Renderer* MainMenuRenderer::GetMainRenderer() const
{
	return renderer;
}

MainMenuRenderer::MainMenuRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont, const MainMenuState& mainMenuState)
	: renderer(renderer)
	, romFont(romFont)
	, mainMenuState(mainMenuState)
{

}

void MainMenuRenderer::Draw() const
{
	romFont.WriteText(GetMainRenderer(), 0, 0, "Start", (mainMenuState == MainMenuState::START) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY));
	romFont.WriteText(GetMainRenderer(), 0, 16, "Quit", (mainMenuState == MainMenuState::QUIT) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY));
}

