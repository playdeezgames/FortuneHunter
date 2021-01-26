#pragma once
#include "BaseRenderer.h"
#include "..\Game\GameData.h"
#include "..\Common\Managers\SpriteManager.h"
#include <map>
class InPlayRenderer : public BaseRenderer
{
private:
	const tggd::common::SpriteManager& spriteManager;
	const GameData& gameData;
	std::map<TerrainType, tggd::common::Sprite*> terrainSprites;
	void DrawRoomPanel() const;//TODO: make this a renderer
	void DrawStatusPanel() const;//TODO: make this a renderer
public:
	InPlayRenderer(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		tggd::common::SpriteManager&,
		const GameData&);
	void Draw() const;
};
