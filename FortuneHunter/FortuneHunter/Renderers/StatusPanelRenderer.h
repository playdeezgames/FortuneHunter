#pragma once
#include "BaseRenderer.h"
#include "..\Game\GameData.h"
class StatusPanelRenderer : public BaseRenderer 
{
private:
	const GameData& gameData;
	void DrawMoves() const;
	void DrawKeys() const;
public:
	StatusPanelRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const GameData&);
	void Draw() const;
};
