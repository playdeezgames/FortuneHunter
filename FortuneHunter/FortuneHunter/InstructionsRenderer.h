#pragma once
#include "BaseMenuRenderer.h"
#include <vector>
#include "Label.h"
class InstructionsRenderer : public BaseMenuRenderer
{
private:
	std::vector<tggd::common::Label> labels;
public:
	InstructionsRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const tggd::common::Sprite*);
	void Draw() const;
};
