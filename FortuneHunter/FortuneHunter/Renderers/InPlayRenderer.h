#pragma once
#include "BaseRenderer.h"
#include "..\Game\GameData.h"
class InPlayRenderer : public BaseRenderer
{
private:
	const GameData& gameData;
	void DrawRoomPanel() const;
public:
	InPlayRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const GameData&);
	void Draw() const;
};
