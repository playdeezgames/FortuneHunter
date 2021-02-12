#include "InPlayRenderer.h"
#include "RoomConstants.h"
#include "ColorConstants.h"
#include "StatusPanelConstants.h"
#include <sstream>
InPlayRenderer::InPlayRenderer(//TODO: give this a background sprite!
	SDL_Renderer* renderer,
	const tggd::common::SpriteFont& romFont,
	const StatusPanelRenderer* statusPanelRenderer,
	const RoomPanelRenderer* roomPanelRenderer,
	const GameData& gameData)
	: BaseRenderer(renderer, romFont)
	, statusPanelRenderer(statusPanelRenderer)
	, roomPanelRenderer(roomPanelRenderer)
	, gameData(gameData)
{
}

void InPlayRenderer::Draw() const
{
	SDL_RenderClear(GetMainRenderer());
	roomPanelRenderer->Draw();
	statusPanelRenderer->Draw();
}

