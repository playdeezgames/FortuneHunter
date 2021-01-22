#include "ConfirmQuitRenderer.h"
#include "..\Constants\Color.h"
ConfirmQuitRenderer::ConfirmQuitRenderer
	(
		SDL_Renderer* renderer,
		const tggd::common::SpriteFont& romFont,
		const ConfirmState& confirmState
	)
	: BaseRenderer(renderer, romFont)
	, confirmState(confirmState)
{

}

void ConfirmQuitRenderer::Draw() const
{
	GetRomFont().WriteText(GetMainRenderer(), 0, 0, "No", (confirmState == ConfirmState::NO) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY));
	GetRomFont().WriteText(GetMainRenderer(), 0, 16, "Yes", (confirmState == ConfirmState::YES) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY));
}
