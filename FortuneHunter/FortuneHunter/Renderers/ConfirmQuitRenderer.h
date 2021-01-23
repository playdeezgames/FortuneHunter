#pragma once
#include "BaseRenderer.h"
#include "..\UI\ConfirmState.h"
class ConfirmQuitRenderer : public BaseRenderer
{
private:
	const ConfirmState& confirmState;
	void DrawConfirmItem(int, const std::string&, const ConfirmState&) const;
public:
	ConfirmQuitRenderer(SDL_Renderer*, const tggd::common::SpriteFont&, const ConfirmState&);
	void Draw() const;
};

