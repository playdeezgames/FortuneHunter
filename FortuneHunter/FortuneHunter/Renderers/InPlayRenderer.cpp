#include "InPlayRenderer.h"
#include "..\Constants\Room.h"
#include "..\Constants\Color.h"
#include "..\Constants\UI.h"
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
	terrainSprites[Terrain::FLOOR] = spriteManager.GetSprite("FloorTile");
	terrainSprites[Terrain::WALL_N] = spriteManager.GetSprite("WallTileN");
	terrainSprites[Terrain::WALL_E] = spriteManager.GetSprite("WallTileE");
	terrainSprites[Terrain::WALL_NE] = spriteManager.GetSprite("WallTileNE");
	terrainSprites[Terrain::WALL_S] = spriteManager.GetSprite("WallTileS");
	terrainSprites[Terrain::WALL_NS] = spriteManager.GetSprite("WallTileNS");
	terrainSprites[Terrain::WALL_ES] = spriteManager.GetSprite("WallTileES");
	terrainSprites[Terrain::WALL_NES] = spriteManager.GetSprite("WallTileNES");
	terrainSprites[Terrain::WALL_W] = spriteManager.GetSprite("WallTileW");
	terrainSprites[Terrain::WALL_NW] = spriteManager.GetSprite("WallTileNW");
	terrainSprites[Terrain::WALL_EW] = spriteManager.GetSprite("WallTileEW");
	terrainSprites[Terrain::WALL_NEW] = spriteManager.GetSprite("WallTileNEW");
	terrainSprites[Terrain::WALL_SW] = spriteManager.GetSprite("WallTileSW");
	terrainSprites[Terrain::WALL_NSW] = spriteManager.GetSprite("WallTileNSW");
	terrainSprites[Terrain::WALL_ESW] = spriteManager.GetSprite("WallTileESW");
	terrainSprites[Terrain::WALL_NESW] = spriteManager.GetSprite("WallTileNESW");

}

void InPlayRenderer::Draw() const
{
	DrawRoomPanel();
}

void InPlayRenderer::DrawRoomPanel() const
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
			int x = column * 16 - 8;
			int y = row * 16 - 8;
			const RoomCell<CreatureType>* cell = gameData.GetRoom().GetCell(column, row);
			Terrain terrain = cell->GetTerrain();
			terrainSprites.find(terrain)->second->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
			const Creature<CreatureType>* creature = cell->GetCreature();
			if (creature != nullptr)
			{
				spriteManager.GetSprite("HunterCreature")->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
			}
		}
	}
	SDL_RenderSetClipRect(GetMainRenderer(), nullptr);
}

