#include "StatusPanelRenderer.h"
#include "StatusPanelConstants.h"
#include "ColorConstants.h"
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
	DrawWounds();
	DrawArmor();
	DrawDiamonds();
	SDL_RenderSetClipRect(GetMainRenderer(), nullptr);
}

void StatusPanelRenderer::DrawMoves() const
{
	std::stringstream ss;
	ss << "M: " << gameData.GetMoves();//TODO magic string
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
	ss << "K: " << gameData.GetHunter()->GetKeys();//TODO magic string
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,
		Constants::UI::StatusPanel::CLIP_Y + 16,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);
}

void StatusPanelRenderer::DrawWounds() const
{
	std::stringstream ss;
	ss << "W: " << gameData.GetHunter()->GetWounds();//TODO magic string
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,
		Constants::UI::StatusPanel::CLIP_Y + 32,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);
}

void StatusPanelRenderer::DrawArmor() const
{
	std::stringstream ss;
	ss << "A: " << gameData.GetHunter()->GetArmor();//TODO magic string
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,
		Constants::UI::StatusPanel::CLIP_Y + 48,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);

}

void StatusPanelRenderer::DrawDiamonds() const
{
	std::stringstream ss;
	ss << "D: " << gameData.GetHunter()->GetDiamonds();//TODO magic string
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,
		Constants::UI::StatusPanel::CLIP_Y + 64,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);

}