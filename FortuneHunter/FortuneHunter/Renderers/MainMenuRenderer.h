#pragma once
#include "..\Common\Renderer.h"
#include "..\Common\SpriteFont.h"
#include "..\Game\MainMenuState.h"
class MainMenuRenderer : public tggd::common::Renderer
{
private:
	SDL_Renderer* renderer;
	tggd::common::SpriteFont romFont;
	const MainMenuState& mainMenuState;
protected:
	SDL_Renderer* GetMainRenderer() const;
public:
	MainMenuRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const MainMenuState&);
	void Draw() const;
};

