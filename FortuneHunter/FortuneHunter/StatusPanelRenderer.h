#pragma once
#include "BaseRenderer.h"
#include "GameData.h"
class StatusPanelRenderer : public BaseRenderer 
{
private:
	const GameData& gameData;
	void DrawMoves() const;
	void DrawKeys() const;
	void DrawWounds() const;
public:
	StatusPanelRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const GameData&);
	void Draw() const;
};
