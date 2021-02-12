#pragma once
#include "BaseMenuRenderer.h"
class AboutRenderer: public BaseMenuRenderer
{
public:
	AboutRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const tggd::common::Sprite*);
	void Draw() const;
};
