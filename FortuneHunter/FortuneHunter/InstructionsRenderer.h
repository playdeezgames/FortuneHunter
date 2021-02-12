#pragma once
#include "BaseMenuRenderer.h"
class InstructionsRenderer : public BaseMenuRenderer
{
public:
	InstructionsRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const tggd::common::Sprite*);
	void Draw() const;
};
