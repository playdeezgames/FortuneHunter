#include "ConfirmQuitRenderer.h"
#include "ColorConstants.h"
#include "ConfirmQuitConstants.h"
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
	GetRomFont().WriteText(GetMainRenderer(), tggd::common::XY<int>(0, 0), Constants::UI::ConfirmQuit::TITLE, Constants::Color::RED);
	DrawConfirmItem(0, Constants::UI::ConfirmQuit::OPTION_NO, ConfirmState::NO);
	DrawConfirmItem(1, Constants::UI::ConfirmQuit::OPTION_YES, ConfirmState::YES);
}

void ConfirmQuitRenderer::DrawConfirmItem(int line, const std::string& text, const ConfirmState& state) const
{
	GetRomFont().WriteText
	(
		GetMainRenderer(),
		tggd::common::XY<int>(0,
		Constants::UI::ConfirmQuit::OFFSET_Y + Constants::UI::ConfirmQuit::LINE_HEIGHT * line),
		text,
		(confirmState == state) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY)
	);
}
