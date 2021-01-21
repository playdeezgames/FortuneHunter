#include "MainMenuRenderer.h"
#include "..\Constants\Color.h"
SDL_Renderer* MainMenuRenderer::GetMainRenderer() const
{
	return renderer;
}

MainMenuRenderer::MainMenuRenderer(SDL_Renderer* renderer, const tggd::common::SpriteManager& spriteManager)
	: renderer(renderer)
	, spriteManager(spriteManager)
{

}

void MainMenuRenderer::Draw() const
{
	spriteManager.GetSprite("Character02")->Draw(GetMainRenderer(), 0, 0, Constants::Color::CYAN);
}

