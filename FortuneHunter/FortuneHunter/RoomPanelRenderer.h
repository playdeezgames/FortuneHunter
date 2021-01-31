#pragma once
#include "BaseRenderer.h"
#include "GameData.h"
#include "TerrainType.h"
#include "TerrainSprites.h"
#include "HealthLevelSprites.h"
class RoomPanelRenderer : public BaseRenderer
{
private:
	const GameData& gameData;
	const tggd::common::SpriteManager& spriteManager;
	const TerrainSprites& terrainSprites;
	const HealthLevelSprites& healthLevelSprites;
	static int PlotColumn(int, int);
	static int PlotRow(int, int);
	void DrawCells() const;
	void DrawCell(int, int) const;
	void DrawTerrain(int, int, TerrainType) const;
	void DrawObject(int, int, const tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>*) const;
	void DrawDither(int, int, const tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*) const;
public:
	RoomPanelRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::SpriteManager&,
		const TerrainSprites&,
		const HealthLevelSprites&,
		const GameData&
	);
	void Draw() const;
};
