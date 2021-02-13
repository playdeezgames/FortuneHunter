#pragma once
#include "BaseMenuRenderer.h"
class FinalScoreRenderer : public BaseMenuRenderer
{
public:
	FinalScoreRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const tggd::common::Sprite*);
	void Draw() const;
};
