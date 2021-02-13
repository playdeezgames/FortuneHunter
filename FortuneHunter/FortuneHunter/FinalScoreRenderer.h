#pragma once
#include "BaseMenuRenderer.h"
#include "GameData.h"
class FinalScoreRenderer : public BaseMenuRenderer
{
private:
	const GameData& gameData;
public:
	FinalScoreRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const tggd::common::Sprite*, const GameData&);
	void Draw() const;
};
