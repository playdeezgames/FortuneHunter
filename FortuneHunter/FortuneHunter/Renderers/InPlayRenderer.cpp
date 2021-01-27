#include "InPlayRenderer.h"
#include "..\Constants\Room.h"
#include "..\Constants\Color.h"
#include "..\Constants\UI\StatusPanel.h"
#include <sstream>
InPlayRenderer::InPlayRenderer(
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
	roomPanelRenderer->Draw();
	statusPanelRenderer->Draw();
}

