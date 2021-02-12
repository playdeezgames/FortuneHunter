#include "InPlayRenderer.h"
#include "RoomConstants.h"
#include "ColorConstants.h"
#include "StatusPanelConstants.h"
#include <sstream>
InPlayRenderer::InPlayRenderer(
	SDL_Renderer* renderer,
	const tggd::common::SpriteFont& romFont,
	const tggd::common::Sprite* background,
	const StatusPanelRenderer* statusPanelRenderer,
	const RoomPanelRenderer* roomPanelRenderer,
	const GameData& gameData)
	: BaseMenuRenderer(renderer, romFont, background)
	, statusPanelRenderer(statusPanelRenderer)
	, roomPanelRenderer(roomPanelRenderer)
	, gameData(gameData)
{
}

void InPlayRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
	roomPanelRenderer->Draw();
	statusPanelRenderer->Draw();
}

