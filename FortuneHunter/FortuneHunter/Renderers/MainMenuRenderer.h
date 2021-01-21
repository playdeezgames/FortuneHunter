#pragma once
#include "..\Common\Renderer.h"
#include "..\Common\SpriteFont.h"
class MainMenuRenderer : public tggd::common::Renderer
{
private:
	SDL_Renderer* renderer;
	tggd::common::SpriteFont romFont;
protected:
	SDL_Renderer* GetMainRenderer() const;
public:
	MainMenuRenderer(SDL_Renderer*, const tggd::common::SpriteFont&);
	void Draw() const;
};

