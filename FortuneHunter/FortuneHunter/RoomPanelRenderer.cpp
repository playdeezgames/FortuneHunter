#include "RoomPanelRenderer.h"
#include "RoomPanelConstants.h"
#include "RoomConstants.h"
#include "ColorConstants.h"
#include "CellConstants.h"
#include "Creature.h"
RoomPanelRenderer::RoomPanelRenderer
(
	SDL_Renderer* renderer,
	const tggd::common::SpriteFont& romFont,
	const tggd::common::SpriteManager& spriteManager,
	const TerrainSpriteManager& terrainSprites,
	const GameData& gameData
)
	: BaseRenderer(renderer, romFont)
	, gameData(gameData)
	, terrainSprites(terrainSprites)
	, spriteManager(spriteManager)
{
}

//TODO: load table from config
const std::string SPRITE_HUNTER = "HunterCreature";
const std::string SPRITE_DITHER = "Dither";
const std::string SPRITE_DOOR_NS = "NSDoor";
const std::string SPRITE_DOOR_EW = "EWDoor";
const std::string SPRITE_KEY = "KeyItem";
const std::string SPRITE_ZOMBIE= "ZombieCreature";
const std::string SPRITE_EXIT = "Exit";
const std::string SPRITE_EXIT_KEY = "ExitKeyItem";
const std::string SPRITE_DIAMOND = "DiamondItem";

void RoomPanelRenderer::DrawTerrain(int x, int y, TerrainType terrain) const
{
	terrainSprites.Get(terrain)->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
}

void RoomPanelRenderer::DrawDither(int x, int y, const tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* cell) const
{
	if (!cell->IsFlagSet(RoomCellFlags::LIT))
	{
		spriteManager.GetSprite(SPRITE_DITHER)->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
	}
}

void RoomPanelRenderer::DrawObject(int x, int y, const tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* object) const
{
	if (object != nullptr)
	{
		ObjectType objectType = object->GetData();
		//TODO: load table from config
		std::string spriteName =
			(objectType == ObjectType::HUNTER) ? (SPRITE_HUNTER) :
			(objectType == ObjectType::DOOR_EW) ? (SPRITE_DOOR_EW) :
			(objectType == ObjectType::DOOR_NS) ? (SPRITE_DOOR_NS) :
			(objectType == ObjectType::ZOMBIE) ? (SPRITE_ZOMBIE) :
			(objectType == ObjectType::EXIT) ? (SPRITE_EXIT) :
			(objectType == ObjectType::EXIT_KEY) ? (SPRITE_EXIT_KEY) :
			(objectType == ObjectType::DIAMOND) ? (SPRITE_DIAMOND) :
			(SPRITE_KEY);
		spriteManager.GetSprite(spriteName)->Draw(GetMainRenderer(), x, y, Constants::Color::WHITE);
	}
}

void RoomPanelRenderer::DrawCell(int column, int row) const
{
	const tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* cell = gameData.GetRoom().GetCell(column, row);
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
