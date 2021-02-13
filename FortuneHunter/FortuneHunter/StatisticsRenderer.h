#pragma once
#include "BaseMenuRenderer.h"
class StatisticsRenderer : public BaseMenuRenderer
{
public:
	StatisticsRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const tggd::common::Sprite*);
	void Draw() const;
};
