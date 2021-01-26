#include "InPlayRenderer.h"
#include "..\Constants\Room.h"
#include "..\Constants\Color.h"
#include "..\Constants\UI.h"
#include <sstream>
InPlayRenderer::InPlayRenderer(
	SDL_Renderer* renderer,
	const tggd::common::SpriteFont& romFont,
	tggd::common::SpriteManager& spriteManager,
	const GameData& gameData)
	: BaseRenderer(renderer, romFont)
	, gameData(gameData)
	, spriteManager(spriteManager)
	, terrainSprites()
{
	terrainSprites[TerrainType::FLOOR] = spriteManager.GetSprite("FloorTile");
	terrainSprites[TerrainType::WALL_N] = spriteManager.GetSprite("WallTileN");
	terrainSprites[TerrainType::WALL_E] = spriteManager.GetSprite("WallTileE");
	terrainSprites[TerrainType::WALL_NE] = spriteManager.GetSprite("WallTileNE");
	terrainSprites[TerrainType::WALL_S] = spriteManager.GetSprite("WallTileS");
	terrainSprites[TerrainType::WALL_NS] = spriteManager.GetSprite("WallTileNS");
	terrainSprites[TerrainType::WALL_ES] = spriteManager.GetSprite("WallTileES");
	terrainSprites[TerrainType::WALL_NES] = spriteManager.GetSprite("WallTileNES");
	terrainSprites[TerrainType::WALL_W] = spriteManager.GetSprite("WallTileW");
	terrainSprites[TerrainType::WALL_NW] = spriteManager.GetSprite("WallTileNW");
	terrainSprites[TerrainType::WALL_EW] = spriteManager.GetSprite("WallTileEW");
	terrainSprites[TerrainType::WALL_NEW] = spriteManager.GetSprite("WallTileNEW");
	terrainSprites[TerrainType::WALL_SW] = spriteManager.GetSprite("WallTileSW");
	terrainSprites[TerrainType::WALL_NSW] = spriteManager.GetSprite("WallTileNSW");
	terrainSprites[TerrainType::WALL_ESW] = spriteManager.GetSprite("WallTileESW");
	terrainSprites[TerrainType::WALL_NESW] = spriteManager.GetSprite("WallTileNESW");

}

void InPlayRenderer::Draw() const
{
	DrawRoomPanel();
	DrawStatusPanel();
}

void InPlayRenderer::DrawStatusPanel() const
{
	SDL_Rect clipRect =
	{
		Constants::UI::InPlay::StatusPanel::CLIP_X,
		Constants::UI::InPlay::StatusPanel::CLIP_Y,
		Constants::UI::InPlay::StatusPanel::CLIP_WIDTH,
		Constants::UI::InPlay::StatusPanel::CLIP_HEIGHT,
	};
	SDL_RenderSetClipRect(GetMainRenderer(), &clipRect);
	std::stringstream ss;
	ss << "Moves: " << gameData.GetMoves();
	GetRomFont().WriteText(
		GetMainRenderer(), 
		Constants::UI::InPlay::StatusPanel::CLIP_X, 
		Constants::UI::InPlay::StatusPanel::CLIP_Y,
		ss.str(),
		Constants::Color::WHITE);
}

void InPlayRenderer::DrawRoomPanel() const//TODO: split this into its own renderer
{
	SDL_Rect clipRect =
	{
		Constants::UI::InPlay::RoomPanel::CLIP_X,
		Constants::UI::InPlay::RoomPanel::CLIP_Y,
		Constants::UI::InPlay::RoomPanel::CLIP_WIDTH,
		Constants::UI::InPlay::RoomPanel::CLIP_HEIGHT,
	};
	SDL_RenderSetClipRect(GetMainRenderer(), &clipRect);
	for (int column = 0; column < Constants::Room::COLUMNS; ++column)
	{
		for (int row = 0; row < Constants::Room::ROWS; ++row)
		{
			const RoomCell<TerrainType, ObjectType>* cell = gameData.GetRoom().GetCell(column, row);
			if (cell->IsExplored())
			{
				int x = column * 16 - 8;
				int y = row * 16 - 8;
				TerrainType terrain = cell->GetTerrain();
				terrainSprites.find(terrain)->second->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
				const RoomCellObject<TerrainType, ObjectType>* creature = cell->GetObject();
				if (creature != nullptr)
				{
					spriteManager.GetSprite("HunterCreature")->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
				}
				if (!cell->IsLit())
				{
					spriteManager.GetSprite("Dither")->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
				}
			}
		}
	}
	SDL_RenderSetClipRect(GetMainRenderer(), nullptr);
}

