#include "InPlayRenderer.h"
InPlayRenderer::InPlayRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont, const GameData& gameData)
	: BaseRenderer(renderer, romFont)
	, gameData(gameData)
{

}

void InPlayRenderer::Draw() const
{
	DrawRoomPanel();
}

void InPlayRenderer::DrawRoomPanel() const
{
}

