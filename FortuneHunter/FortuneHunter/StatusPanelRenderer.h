#pragma once
#include "BaseRenderer.h"
#include "GameData.h"
#include "SpriteManager.h"
class StatusPanelRenderer : public BaseRenderer 
{
private:
	const GameData& gameData;
	const tggd::common::SpriteManager& spriteManager;
	void DrawMoves() const;
	void DrawKeys() const;
	void DrawWounds() const;
	void DrawArmor() const;
	void DrawAttack() const;
	void DrawDiamonds() const;
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
