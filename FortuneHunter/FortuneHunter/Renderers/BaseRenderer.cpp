#include "BaseRenderer.h"
SDL_Renderer* BaseRenderer::GetMainRenderer() const
{
	return renderer;
}

const tggd::common::SpriteFont& BaseRenderer::GetRomFont() const
{
	return romFont;
}

BaseRenderer::BaseRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont)
	: renderer(renderer)
	, romFont(romFont)
{

}
