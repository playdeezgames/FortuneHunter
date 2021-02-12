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
	const TerrainSprites& terrainSprites,
	const HealthLevelSprites& healthLevelSprites,
	const ObjectSprites& objectSprites,
	const GameData& gameData
)
	: BaseRenderer(renderer, romFont)
	, gameData(gameData)
	, terrainSprites(terrainSprites)
	, healthLevelSprites(healthLevelSprites)
	, spriteManager(spriteManager)
	, objectSprites(objectSprites)
{
}

const std::string SPRITE_DITHER = "Dither";
const std::string SPRITE_UNEXPLORED = "Unexplored";

void RoomPanelRenderer::DrawTerrain(const tggd::common::XY<int>& xy, TerrainType terrain) const
{
	terrainSprites.Get(terrain)->Draw(GetMainRenderer(), xy, Constants::Color::WHITE);
}

void RoomPanelRenderer::DrawDither(const tggd::common::XY<int>& xy, const tggd::common::RoomCell<TerrainType, ObjectType, RoomCellFlags>* cell) const
{
	if (!cell->IsFlagSet(RoomCellFlags::LIT))
	{
		spriteManager.GetSprite(SPRITE_DITHER)->Draw(GetMainRenderer(), xy, Constants::Color::WHITE);
	}
}

void RoomPanelRenderer::DrawObject(const tggd::common::XY<int>& xy, const tggd::common::RoomCellObject<TerrainType, ObjectType, RoomCellFlags>* object) const
{
	if (object != nullptr)
	{
		ObjectType objectType = object->GetData();
		auto sprite= objectSprites.Get(objectType);
		sprite->Draw(GetMainRenderer(), xy, Constants::Color::WHITE);
		const Creature* creature = dynamic_cast<const Creature*>(object);
		if (creature && creature->GetRoomCell() && creature->GetRoomCell()->IsFlagSet(RoomCellFlags::LIT))
		{
			auto level = creature->GetHealthLevel();
			auto sprite = healthLevelSprites.Get(level);
			if (sprite)
			{
				sprite->Draw(GetMainRenderer(), xy, Constants::Color::WHITE);
			}
		}
	}
}

void RoomPanelRenderer::DrawUnexplored(const tggd::common::XY<int>& xy) const
{
	spriteManager.GetSprite(SPRITE_UNEXPLORED)->Draw(GetMainRenderer(), xy, Constants::Color::WHITE);
}


void RoomPanelRenderer::DrawCell(int column, int row) const
{
	auto cell = gameData.GetRoom().GetCell(column, row);
	tggd::common::XY xy(PlotColumn(column, row), PlotRow(column, row));
	if (cell->IsFlagSet(RoomCellFlags::EXPLORED))
	{
		DrawTerrain(xy, cell->GetTerrain());
		DrawObject(xy, cell->GetObject());
		DrawDither(xy, cell);
	}
	else
	{
		DrawUnexplored(xy);
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
