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

void StatusPanelRenderer::DrawGameOver() const
{
	if (!gameData.GetHunter()->IsAlive())
	{
		GetRomFont().WriteText(
			GetMainRenderer(),
			Constants::UI::StatusPanel::CLIP_X,
			Constants::UI::StatusPanel::CLIP_Y + 96,//TODO: magic number
			"Yer dead!",//TODO: magic string
			Constants::Color::RED);
	}
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
	DrawAttack();
	DrawGameOver();
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
	ss << "H: " << gameData.GetHunter()->GetHealth() << "/" << gameData.GetHunter()->GetMaximumHealth();//TODO magic string
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
	ss << "A: " << gameData.GetHunter()->GetArmor() << "/" << gameData.GetHunter()->GetMaximumArmor();//TODO magic string
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,
		Constants::UI::StatusPanel::CLIP_Y + 48,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);

}

void StatusPanelRenderer::DrawAttack() const
{
	std::stringstream ss;
	ss << "X: " << gameData.GetHunter()->GetMaximumAttack();//TODO magic string
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,
		Constants::UI::StatusPanel::CLIP_Y + 80,//TODO: magic number
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