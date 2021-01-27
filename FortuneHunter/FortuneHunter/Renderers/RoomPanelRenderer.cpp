#include "RoomPanelRenderer.h"
#include "..\Constants\UI\RoomPanel.h"
#include "..\Constants\Room.h"
#include "..\Constants\Color.h"
#include "..\Constants\Cell.h"
RoomPanelRenderer::RoomPanelRenderer
(
	SDL_Renderer* renderer,
	const tggd::common::SpriteFont& romFont,
	const tggd::common::SpriteManager& spriteManager,
	const GameData& gameData
)
	: BaseRenderer(renderer, romFont)
	, gameData(gameData)
	, terrainSprites()
	, spriteManager(spriteManager)

{
	terrainSprites[TerrainType::FLOOR] = spriteManager.GetSprite("FloorTile");//TODO magic strings
	terrainSprites[TerrainType::WALL_N] = spriteManager.GetSprite("WallTileN");//TODO magic strings
	terrainSprites[TerrainType::WALL_E] = spriteManager.GetSprite("WallTileE");//TODO magic strings
	terrainSprites[TerrainType::WALL_NE] = spriteManager.GetSprite("WallTileNE");//TODO magic strings
	terrainSprites[TerrainType::WALL_S] = spriteManager.GetSprite("WallTileS");//TODO magic strings
	terrainSprites[TerrainType::WALL_NS] = spriteManager.GetSprite("WallTileNS");//TODO magic strings
	terrainSprites[TerrainType::WALL_ES] = spriteManager.GetSprite("WallTileES");//TODO magic strings
	terrainSprites[TerrainType::WALL_NES] = spriteManager.GetSprite("WallTileNES");//TODO magic strings
	terrainSprites[TerrainType::WALL_W] = spriteManager.GetSprite("WallTileW");//TODO magic strings
	terrainSprites[TerrainType::WALL_NW] = spriteManager.GetSprite("WallTileNW");//TODO magic strings
	terrainSprites[TerrainType::WALL_EW] = spriteManager.GetSprite("WallTileEW");//TODO magic strings
	terrainSprites[TerrainType::WALL_NEW] = spriteManager.GetSprite("WallTileNEW");//TODO magic strings
	terrainSprites[TerrainType::WALL_SW] = spriteManager.GetSprite("WallTileSW");//TODO magic strings
	terrainSprites[TerrainType::WALL_NSW] = spriteManager.GetSprite("WallTileNSW");//TODO magic strings
	terrainSprites[TerrainType::WALL_ESW] = spriteManager.GetSprite("WallTileESW");//TODO magic strings
	terrainSprites[TerrainType::WALL_NESW] = spriteManager.GetSprite("WallTileNESW");//TODO magic strings
}

const std::string SPRITE_HUNTER = "HunterCreature";
const std::string SPRITE_DITHER = "Dither";

void RoomPanelRenderer::DrawTerrain(int x, int y, TerrainType terrain) const
{
	terrainSprites.find(terrain)->second->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
}

void RoomPanelRenderer::DrawDither(int x, int y, const RoomCell<TerrainType, ObjectType>* cell) const
{
	if (!cell->IsLit())
	{
		spriteManager.GetSprite(SPRITE_DITHER)->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
	}
}

void RoomPanelRenderer::DrawObject(int x, int y, const RoomCellObject<TerrainType, ObjectType>* object) const
{
	if (object != nullptr)
	{
		spriteManager.GetSprite(SPRITE_HUNTER)->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
	}
}

void RoomPanelRenderer::DrawCell(int column, int row) const
{
	const RoomCell<TerrainType, ObjectType>* cell = gameData.GetRoom().GetCell(column, row);
	if (cell->IsExplored())
	{
		int x = PlotColumn(column, row);
		int y = PlotRow(column, row);

		DrawTerrain(x, y, cell->GetTerrain());
		DrawObject(x, y, cell->GetObject());
		DrawDither(x, y, cell);
	}
}

void RoomPanelRenderer::DrawCells() const
{
	for (int column = 0; column < Constants::Room::COLUMNS; ++column)
	{
		for (int row = 0; row < Constants::Room::ROWS; ++row)
		{
			DrawCell(column, row);
		}
	}
}

void RoomPanelRenderer::Draw() const
{
	SDL_Rect clipRect =
	{
		Constants::UI::RoomPanel::CLIP_X,
		Constants::UI::RoomPanel::CLIP_Y,
		Constants::UI::RoomPanel::CLIP_WIDTH,
		Constants::UI::RoomPanel::CLIP_HEIGHT,
	};
	SDL_RenderSetClipRect(GetMainRenderer(), &clipRect);
	DrawCells();
	SDL_RenderSetClipRect(GetMainRenderer(), nullptr);

}

int RoomPanelRenderer::PlotColumn(int column, int row)
{
	return column * Constants::Cell::WIDTH - (Constants::Cell::WIDTH / 2);
}

int RoomPanelRenderer::PlotRow(int column, int row)
{
	return row * Constants::Cell::HEIGHT - (Constants::Cell::HEIGHT / 2);
}
