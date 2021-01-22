#pragma once
#include "BaseRenderer.h"
#include "..\Game\ConfirmState.h"
class ConfirmQuitRenderer : public BaseRenderer
{
private:
	const ConfirmState& confirmState;
public:
	ConfirmQuitRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const ConfirmState&);
	void Draw() const;
};

