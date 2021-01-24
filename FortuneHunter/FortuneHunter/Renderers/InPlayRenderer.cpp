#include "InPlayRenderer.h"
#include "..\Constants\Room.h"
#include "..\Constants\Color.h"
InPlayRenderer::InPlayRenderer(SDL_Renderer* renderer, const tggd::common::SpriteFont& romFont, const GameData& gameData)
	: BaseRenderer(renderer, romFont)
	, gameData(gameData)
{

}

void InPlayRenderer::Draw() const
{
	DrawRoomPanel();
}

void InPlayRenderer::DrawRoomPanel() const
{
	for (int column = 0; column < Constants::Room::COLUMNS; ++column)
	{
		for (int row = 0; row < Constants::Room::ROWS; ++row)
		{
			int x = column * 16 - 8;
			int y = row * 16 - 8;
			switch (gameData.GetRoom().GetCell(column, row).GetTerrain())
			{
			case Terrain::WALL:
				GetRomFont().WriteGlyph(GetMainRenderer(), x, y, '#', Constants::Color::BLUE);
				break;
			}
		}
	}
}

