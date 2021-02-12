#pragma once
#include "BaseRenderer.h"
#include "GameData.h"
#include "TerrainType.h"
#include "TerrainSprites.h"
#include "HealthLevelSprites.h"
#include "ObjectSprites.h"
#include "XY.h"
class RoomPanelRenderer : public BaseRenderer
{
private:
	const GameData& gameData;
	const tggd::common::SpriteManager& spriteManager;
	const TerrainSprites& terrainSprites;
	const HealthLevelSprites& healthLevelSprites;
	const ObjectSprites& objectSprites;
	static int PlotColumn(int, int);
	static int PlotRow(int, int);
	void DrawCells() const;
	void DrawCell(int, int) const;
	void DrawTerrain(const tggd::common::XY<int>&, TerrainType) const;
	void DrawUnexplored(const tggd::common::XY<int>&) const;
	void DrawExplored
	(
		const tggd::common::XY<int>&, 
		const tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*
	) const;
	void DrawObject
	(
		const tggd::common::XY<int>&, 
		const tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>*
	) const;
	void DrawHealthLevel
	(
		const tggd::common::XY<int>&, 
		const tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>*
	) const;
	void DrawDither
	(
		const tggd::common::XY<int>&, 
		const tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>*
	) const;
public:
	RoomPanelRenderer
	(
		SDL_Renderer*, 
		const tggd::common::SpriteFont&, 
		const tggd::common::SpriteManager&,
		const TerrainSprites&,
		const HealthLevelSprites&,
		const ObjectSprites&,
		const GameData&
	);
	void Draw() const;
};
