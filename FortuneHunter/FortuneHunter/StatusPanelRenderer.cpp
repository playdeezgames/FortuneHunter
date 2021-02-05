#include "StatusPanelRenderer.h"
#include "StatusPanelConstants.h"
#include "ColorConstants.h"
#include <sstream>
StatusPanelRenderer::StatusPanelRenderer
	(
		SDL_Renderer* renderer, 
		const tggd::common::SpriteFont& romFont, 
		const tggd::common::SpriteManager& spriteManager,
		const GameData& gameData
	)
	: BaseRenderer(renderer, romFont)
	, gameData(gameData)
	, spriteManager(spriteManager)
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
	else if (gameData.GetHunter()->IsWinner())
	{
		GetRomFont().WriteText(
			GetMainRenderer(),
			Constants::UI::StatusPanel::CLIP_X,
			Constants::UI::StatusPanel::CLIP_Y + 96,//TODO: magic number
			"You win!",//TODO: magic string
			Constants::Color::LIGHT_GREEN);
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
	ss << gameData.GetMoves();//TODO magic string
	spriteManager.GetSprite("MoveIcon")->Draw//TODO magic string
	(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y,//TODO: magic number
		Constants::Color::WHITE
	);
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X + 16,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y,
		ss.str(),
		Constants::Color::WHITE);
}

void StatusPanelRenderer::DrawKeys() const
{
	std::stringstream ss;
	ss << gameData.GetHunter()->GetKeys();//TODO magic string
	spriteManager.GetSprite("KeyItem")->Draw//TODO magic string
	(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y + 16,//TODO: magic number
		Constants::Color::WHITE
	);
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X + 16,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y + 16,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);
}

void StatusPanelRenderer::DrawWounds() const
{
	std::stringstream ss;
	ss << gameData.GetHunter()->GetHealth() << "/" << gameData.GetHunter()->GetMaximumHealth();//TODO magic string
	spriteManager.GetSprite("PotionItem")->Draw//TODO magic string
	(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y + 32,//TODO: magic number
		Constants::Color::WHITE
	);
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X + 16,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y + 32,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);
}

void StatusPanelRenderer::DrawArmor() const
{
	std::stringstream ss;
	ss << gameData.GetHunter()->GetArmor() << "/" << gameData.GetHunter()->GetMaximumArmor();//TODO magic string
	spriteManager.GetSprite("ShieldItem")->Draw//TODO magic string
	(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y+48,//TODO: magic number
		Constants::Color::WHITE
	);
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X + 16,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y + 48,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);

}

void StatusPanelRenderer::DrawAttack() const
{
	std::stringstream ss;
	ss << gameData.GetHunter()->GetMaximumAttack();//TODO magic string
	spriteManager.GetSprite("SwordItem")->Draw//TODO magic string
	(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y + 80,//TODO: magic number
		Constants::Color::WHITE
	);
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X + 16,
		Constants::UI::StatusPanel::CLIP_Y + 80,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);
}


void StatusPanelRenderer::DrawDiamonds() const
{
	std::stringstream ss;
	ss << gameData.GetHunter()->GetDiamonds();//TODO magic string
	spriteManager.GetSprite("DiamondItem")->Draw//TODO magic string
	(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y + 64,//TODO: magic number
		Constants::Color::WHITE
	);
	GetRomFont().WriteText(
		GetMainRenderer(),
		Constants::UI::StatusPanel::CLIP_X + 16,//TODO: magic number
		Constants::UI::StatusPanel::CLIP_Y + 64,//TODO: magic number
		ss.str(),
		Constants::Color::WHITE);

}