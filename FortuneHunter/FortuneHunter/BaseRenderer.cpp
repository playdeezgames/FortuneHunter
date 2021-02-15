#include "BaseRenderer.h"
SDL_Renderer* BaseRenderer::GetRenderer() const
{
	return renderer;
}

const tggd::common::SpriteFont& BaseRenderer::GetFont() const
{
	return romFont;
}

BaseRenderer::BaseRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont)
	: renderer(renderer)
	, romFont(romFont)
{

}
