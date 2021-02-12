#include "InstructionsRenderer.h"
#include "ColorConstants.h"
InstructionsRenderer::InstructionsRenderer
(
	SDL_Renderer* renderer, 
	const tggd::common::SpriteFont& romFont,
	const tggd::common::Sprite* background
)
	: BaseMenuRenderer(renderer, romFont, background)
{

}

void InstructionsRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
	GetRomFont().WriteText(GetMainRenderer(), tggd::common::XY<int>(0, 0), "Instructions", Constants::Color::GREEN);
	GetRomFont().WriteText(GetMainRenderer(), tggd::common::XY<int>(0, 32), "TODO: put some information here!", Constants::Color::GRAY);
}
