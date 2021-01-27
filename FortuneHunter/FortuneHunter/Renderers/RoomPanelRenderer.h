#pragma once
#include "BaseRenderer.h"
#include "..\Game\GameData.h"
#include "..\Game\TerrainType.h"
class RoomPanelRenderer : public BaseRenderer
{
private:
	const GameData& gameData;
	std::map<TerrainType, tggd::common::Sprite*> terrainSprites;
	const tggd::common::SpriteManager& spriteManager;
public:
	RoomPanelRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::SpriteManager&,
		const GameData&
	);
	void Draw() const;
};
