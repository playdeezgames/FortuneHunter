#include "AboutRenderer.h"
#include "ColorConstants.h"
AboutRenderer::AboutRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont)
	: BaseRenderer(renderer, romFont)
{

}

void AboutRenderer::Draw() const
{
	GetRomFont().WriteText(GetMainRenderer(), 0, 0, "About", Constants::Color::GREEN);
	GetRomFont().WriteText(GetMainRenderer(), 0, 32, "TODO: put some information here!", Constants::Color::GRAY);
}
