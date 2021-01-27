#pragma once
#include "BaseRenderer.h"
#include "..\Game\GameData.h"
#include "..\Common\Managers\SpriteManager.h"
#include <map>
#include "StatusPanelRenderer.h"
#include "RoomPanelRenderer.h"
class InPlayRenderer : public BaseRenderer
{
private:
	const StatusPanelRenderer* statusPanelRenderer;
	const RoomPanelRenderer* roomPanelRenderer;
	const GameData& gameData;
public:
	InPlayRenderer(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const StatusPanelRenderer*,
		const RoomPanelRenderer*,
		const GameData&);
	void Draw() const;
};
