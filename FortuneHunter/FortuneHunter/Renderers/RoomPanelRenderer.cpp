#include "RoomPanelRenderer.h"
#include "..\Constants\UI\RoomPanel.h"
#include "..\Constants\Room.h"
#include "..\Constants\Color.h"
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
	for (int column = 0; column < Constants::Room::COLUMNS; ++column)
	{
		for (int row = 0; row < Constants::Room::ROWS; ++row)
		{
			const RoomCell<TerrainType, ObjectType>* cell = gameData.GetRoom().GetCell(column, row);
			if (cell->IsExplored())
			{
				int x = column * 16 - 8;//TODO magic number
				int y = row * 16 - 8;//TODO magic number
				TerrainType terrain = cell->GetTerrain();
				terrainSprites.find(terrain)->second->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
				const RoomCellObject<TerrainType, ObjectType>* creature = cell->GetObject();
				if (creature != nullptr)
				{
					spriteManager.GetSprite("HunterCreature")->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);//TODO magic string
				}
				if (!cell->IsLit())
				{
					spriteManager.GetSprite("Dither")->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);//TODO magic string
				}
			}
		}
	}
	SDL_RenderSetClipRect(GetMainRenderer(), nullptr);

}
