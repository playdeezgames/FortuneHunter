#pragma once
#include "BaseMenuRenderer.h"
#include "GameData.h"
#include "SpriteManager.h"
#include <map>
#include "StatusPanelRenderer.h"
#include "RoomPanelRenderer.h"
class InPlayRenderer : public BaseMenuRenderer
{
private:
	const StatusPanelRenderer* statusPanelRenderer;
	const RoomPanelRenderer* roomPanelRenderer;
	const GameData& gameData;
public:
	InPlayRenderer(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::Sprite*,
		const StatusPanelRenderer*,
		const RoomPanelRenderer*,
		const GameData&);
	void Draw() const;
};
