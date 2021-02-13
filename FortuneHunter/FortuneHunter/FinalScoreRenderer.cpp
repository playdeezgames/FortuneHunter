#include "FinalScoreRenderer.h"
FinalScoreRenderer::FinalScoreRenderer
(
	SDL_Renderer* renderer, 
	const tggd::common::SpriteFont& romFont, 
	const tggd::common::Sprite* background
)
	: BaseMenuRenderer(renderer, romFont, background)
{

}

void FinalScoreRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
}
