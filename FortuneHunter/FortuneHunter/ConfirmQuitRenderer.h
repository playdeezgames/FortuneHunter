#pragma once
#include "BaseMenuRenderer.h"
#include "ConfirmState.h"
class ConfirmQuitRenderer : public BaseMenuRenderer
{
private:
	const ConfirmState& confirmState;
	void DrawConfirmItem(int, const std::string&, const ConfirmState&) const;
public:
	ConfirmQuitRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::Sprite*,
		const ConfirmState&
	);
	void Draw() const;
};

