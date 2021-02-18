#include "ConfirmQuitRenderer.h"
#include "ColorConstants.h"
#include "ConfirmQuitConstants.h"
ConfirmQuitRenderer::ConfirmQuitRenderer
	(
		SDL_Renderer* renderer,
		const tggd::common::SpriteFont& romFont,
		const tggd::common::Sprite* background,
		const ConfirmState& confirmState
	)
	: BaseMenuRenderer(renderer, romFont, background)
	, confirmState(confirmState)
{

}

void ConfirmQuitRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(324, 124), Constants::UI::ConfirmQuit::TITLE, Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(320, 120), Constants::UI::ConfirmQuit::TITLE, Constants::Color::RED);
	DrawConfirmItem(0, Constants::UI::ConfirmQuit::OPTION_NO, ConfirmState::NO);
	DrawConfirmItem(1, Constants::UI::ConfirmQuit::OPTION_YES, ConfirmState::YES);
}

void ConfirmQuitRenderer::DrawConfirmItem(int line, const std::string& text, const ConfirmState& state) const
{
	GetFont().WriteTextCentered
	(
		GetRenderer(),
		tggd::common::XY<int>(324,
			Constants::UI::ConfirmQuit::OFFSET_Y + Constants::UI::ConfirmQuit::LINE_HEIGHT * line + 4),
		text,
		Constants::Color::BLACK
	);
	GetFont().WriteTextCentered
	(
		GetRenderer(),
		tggd::common::XY<int>(320,
		Constants::UI::ConfirmQuit::OFFSET_Y + Constants::UI::ConfirmQuit::LINE_HEIGHT * line),
		text,
		(confirmState == state) ? (Constants::Color::YELLOW) : (Constants::Color::GRAY)
	);
}
