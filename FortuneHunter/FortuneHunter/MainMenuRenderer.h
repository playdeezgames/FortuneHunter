#pragma once
#include "BaseMenuRenderer.h"
#include "MainMenuState.h"
#include "GameData.h"
#include "Sprite.h"
#include "HunterDescriptorManager.h"
class MainMenuRenderer : public BaseMenuRenderer
{
private:
	const MainMenuState& mainMenuState;
	void DrawMenuItem(int, const std::string&, const MainMenuState&) const;
	const GameData& gameData;
	const HunterDescriptorManager& hunterDescriptors;
public:
	MainMenuRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::Sprite*, 
		const MainMenuState&, 
		const GameData&,
		const HunterDescriptorManager&
	);
	void Draw() const;
};

