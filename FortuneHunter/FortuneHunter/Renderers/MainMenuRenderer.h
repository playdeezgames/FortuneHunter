#pragma once
#include "BaseRenderer.h"
#include "..\Game\MainMenuState.h"
class MainMenuRenderer : public BaseRenderer
{
private:
	const MainMenuState& mainMenuState;
public:
	MainMenuRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const MainMenuState&);
	void Draw() const;
};

