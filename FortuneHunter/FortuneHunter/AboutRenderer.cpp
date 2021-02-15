#include "AboutRenderer.h"
#include "ColorConstants.h"
AboutRenderer::AboutRenderer
(
	SDL_Renderer* renderer, 
	const tggd::common::SpriteFont& romFont,
	const tggd::common::Sprite* background
)
	: BaseMenuRenderer(renderer, romFont, background)
{

}

void AboutRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
	GetFont().WriteText(GetRenderer(), tggd::common::XY<int>(0, 0), "About", Constants::Color::GREEN);
	GetFont().WriteText(GetRenderer(), tggd::common::XY<int>(0, 32), "TODO: put some information here!", Constants::Color::GRAY);
}
