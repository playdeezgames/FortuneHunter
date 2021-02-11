#include "InstructionsRenderer.h"
#include "ColorConstants.h"
InstructionsRenderer::InstructionsRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont)
	: BaseRenderer(renderer, romFont)
{

}

void InstructionsRenderer::Draw() const
{
	GetRomFont().WriteText(GetMainRenderer(), 0, 0, "Instructions", Constants::Color::GREEN);
	GetRomFont().WriteText(GetMainRenderer(), 0, 32, "TODO: put some information here!", Constants::Color::GRAY);
}
