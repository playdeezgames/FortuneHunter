#pragma once
#include "BaseRenderer.h"
class InstructionsRenderer : public BaseRenderer
{
public:
	InstructionsRenderer(SDL_Renderer*, const tggd::common::SpriteFont&);
	void Draw() const;
};
