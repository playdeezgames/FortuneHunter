#pragma once
#include "BaseRenderer.h"
#include "..\Game\GameData.h"
#include "..\Game\TerrainType.h"
#include "..\Game\TerrainSpriteManager.h"
class RoomPanelRenderer : public BaseRenderer
{
private:
	const GameData& gameData;
	const tggd::common::SpriteManager& spriteManager;
	const TerrainSpriteManager& terrainSprites;
	static int PlotColumn(int, int);
	static int PlotRow(int, int);
	void DrawCells() const;
	void DrawCell(int, int) const;
	void DrawTerrain(int, int, TerrainType) const;
	void DrawObject(int, int, const RoomCellObject<TerrainType, ObjectType>*) const;
	void DrawDither(int, int, const RoomCell<TerrainType, ObjectType>*) const;
public:
	RoomPanelRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::SpriteManager&,
		const TerrainSpriteManager&,
		const GameData&
	);
	void Draw() const;
};
