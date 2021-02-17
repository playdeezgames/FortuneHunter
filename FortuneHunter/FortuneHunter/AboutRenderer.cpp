#include "AboutRenderer.h"
#include "ColorConstants.h"
AboutRenderer::AboutRenderer
(
	SDL_Renderer* renderer, 
	const tggd::common::SpriteFont& romFont,
	const tggd::common::Sprite* background
)
	: BaseMenuRenderer(renderer, romFont, background)
{

}

void AboutRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(324, 164), "==About Fortune Hunter==", Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(320, 160), "==About Fortune Hunter==", Constants::Color::LIGHT_GREEN);

	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(324, 324), "A Production of TheGrumpyGameDev", Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(320, 320), "A Production of TheGrumpyGameDev", Constants::Color::GRAY);

	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(324, 340), "https://thegrumpygamedev.itch.io/", Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(320, 336), "https://thegrumpygamedev.itch.io/", Constants::Color::LIGHT_BLUE);

	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(324, 356), "(URL copied to clipboard!)", Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY<int>(320, 352), "(URL copied to clipboard!)", Constants::Color::DARK_GRAY);
}
