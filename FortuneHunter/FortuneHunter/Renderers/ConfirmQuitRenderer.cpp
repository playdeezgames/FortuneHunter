#include "ConfirmQuitRenderer.h"
#include "..\Constants\Color.h"
#include "..\Constants\UI.h"
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
	GetRomFont().WriteText(GetMainRenderer(), 0, 0, "Are you sure you want to quit?", Constants::Color::RED);//TODO magic string
	DrawConfirmItem(0, "No", ConfirmState::NO);//TODO magic string
	DrawConfirmItem(1, "Yes", ConfirmState::YES);//TODO magic string
}

void ConfirmQuitRenderer::DrawConfirmItem(int line, const std::string& text, const ConfirmState& state) const
{
	GetRomFont().WriteText
	(
		GetMainRenderer(),
		0,
		Constants::UI::ConfirmQuit::OFFSET_Y + Constants::UI::ConfirmQuit::LINE_HEIGHT * line,
		text,
		(confirmState == state) ? (Constants::Color::LIGHT_BLUE) : (Constants::Color::GRAY)
	);
}
