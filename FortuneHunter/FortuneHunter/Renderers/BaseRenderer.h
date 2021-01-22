#pragma once
#include "..\Common\Renderer.h"
#include "..\Common\SpriteFont.h"
class BaseRenderer : public tggd::common::Renderer
{
private:
	SDL_Renderer* renderer;
	const tggd::common::SpriteFont& romFont;
protected:
	SDL_Renderer* GetMainRenderer() const;
	const tggd::common::SpriteFont& GetRomFont() const;
public:
	BaseRenderer(SDL_Renderer*, const tggd::common::SpriteFont&);
};
