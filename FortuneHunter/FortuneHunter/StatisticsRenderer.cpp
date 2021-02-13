#include "StatisticsRenderer.h"
StatisticsRenderer::StatisticsRenderer
(
	SDL_Renderer* renderer,
	const tggd::common::SpriteFont& romFont,
	const tggd::common::Sprite* background
)
	: BaseMenuRenderer(renderer, romFont, background)
{

}

void StatisticsRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
}
