#include "MainMenuRenderer.h"
#include "..\Constants\Color.h"
SDL_Renderer* MainMenuRenderer::GetMainRenderer() const
{
	return renderer;
}

MainMenuRenderer::MainMenuRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont)
	: renderer(renderer)
	, romFont(romFont)
{

}

void MainMenuRenderer::Draw() const
{
	romFont.WriteText(GetMainRenderer(), 0, 0, "Hunt that fortune!!", Constants::Color::LIGHT_GREEN);
}

