#pragma once
#include "BaseRenderer.h"
#include "GameData.h"
#include "SpriteManager.h"
#include "XY.h"
class StatusPanelRenderer : public BaseRenderer 
{
private:
	const GameData& gameData;
	const tggd::common::SpriteManager& spriteManager;
	void DrawStatistic(const std::string&, const tggd::common::XY<int>&, const std::string&, const tggd::common::XY<int>&) const;
	void DrawMoves() const;
	void DrawKeys() const;
	void DrawWounds() const;
	void DrawArmor() const;
	void DrawAttack() const;
	void DrawDiamonds() const;
	void DrawBombs() const;
	void DrawGameOver() const;
public:
	StatusPanelRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::SpriteManager&,
		const GameData&
	);
	void Draw() const;
};
