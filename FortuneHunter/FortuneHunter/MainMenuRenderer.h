#pragma once
#include "BaseRenderer.h"
#include "MainMenuState.h"
class MainMenuRenderer : public BaseRenderer
{
private:
	const MainMenuState& mainMenuState;
	void DrawMenuItem(int, const std::string&, const MainMenuState&) const;
public:
	MainMenuRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const MainMenuState&);
	void Draw() const;
};

