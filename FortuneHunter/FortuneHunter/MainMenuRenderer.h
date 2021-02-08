#pragma once
#include "BaseRenderer.h"
#include "MainMenuState.h"
#include "GameData.h"
class MainMenuRenderer : public BaseRenderer
{
private:
	const MainMenuState& mainMenuState;
	void DrawMenuItem(int, const std::string&, const MainMenuState&) const;
	const GameData& gameData;
public:
	MainMenuRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const MainMenuState&, const GameData&);
	void Draw() const;
};

