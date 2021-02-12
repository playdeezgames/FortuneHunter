#include "BaseMenuRenderer.h"
#include "ColorConstants.h"
BaseMenuRenderer::BaseMenuRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont, const tggd::common::Sprite* background)
	: BaseRenderer(renderer, romFont)
	, background(background)
{

}
void BaseMenuRenderer::Draw() const
{
	background->Draw(GetMainRenderer(), tggd::common::XY<int>(0, 0), Constants::Color::WHITE);
}
