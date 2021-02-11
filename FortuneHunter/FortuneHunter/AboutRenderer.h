#pragma once
#include "BaseRenderer.h"
class AboutRenderer: public BaseRenderer
{
public:
	AboutRenderer(SDL_Renderer*, const tggd::common::SpriteFont&);
	void Draw() const;
};
