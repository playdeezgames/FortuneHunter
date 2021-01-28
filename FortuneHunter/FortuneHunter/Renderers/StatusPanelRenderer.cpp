#include "StatusPanelRenderer.h"
#include "..\Constants\UI\StatusPanel.h"
#include "..\Constants\Color.h"
#include <sstream>
StatusPanelRenderer::StatusPanelRenderer
	(
		SDL_Renderer* renderer, 
		const tggd::common::SpriteFont& romFont, 
		const GameData& gameData)
	: BaseRenderer(renderer, romFont)
	, gameData(gameData)
{

}

void StatusPanelRenderer::Draw() const
{
	SDL_Rect clipRect =
	{
		Constants::UI::StatusPanel::CLIP_X,
		Constants::UI::StatusPanel::CLIP_Y,
		Constants::UI::StatusPanel::CLIP_WIDTH,
		Constants::UI::StatusPanel::CLIP_HEIGHT,
	};
	SDL_RenderSetClipRect(GetMainRenderer(), &clipRect);
	DrawMoves();
	DrawKeys();
	SDL_RenderSetClipRect(GetMainRenderer(), nullptr);
}

void StatusPanelRenderer::DrawMoves() const
{
	std::stringstream ss;
	ss << "Moves: " << gameData.GetMoves();//TODO magic string
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,
		Constants::UI::StatusPanel::CLIP_Y,
		ss.str(),
		Constants::Color::WHITE);
}

void StatusPanelRenderer::DrawKeys() const
{
	std::stringstream ss;
	ss << "Keys: " << gameData.GetHunter()->GetKeys();//TODO magic string
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,
		Constants::UI::StatusPanel::CLIP_Y + 16,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);
}
