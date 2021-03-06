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
		GetFont().WriteText(
			GetRenderer(),
			tggd::common::XY<int>(Constants::UI::StatusPanel::CLIP_X,
			Constants::UI::StatusPanel::CLIP_Y + 112),//TODO: magic number
			"Yer dead!",//TODO: magic string
			Constants::Color::RED);
	}
	else if (gameData.GetHunter()->IsWinner())
	{
		GetFont().WriteText(
			GetRenderer(),
			tggd::common::XY<int>(Constants::UI::StatusPanel::CLIP_X,
			Constants::UI::StatusPanel::CLIP_Y + 112),//TODO: magic number
			"You win!",//TODO: magic string
			Constants::Color::LIGHT_GREEN);
	}
}

void StatusPanelRenderer::DrawBombs() const
{
	std::stringstream ss;
	ss << gameData.GetHunter()->GetBombs();
	spriteManager.GetSprite(Constants::UI::StatusPanel::BOMBS_ICON_SPRITE_NAME)->Draw
	(
		GetRenderer(),
		tggd::common::XY<int>(
		Constants::UI::StatusPanel::BOMBS_ICON_X,
		Constants::UI::StatusPanel::BOMBS_ICON_Y)
	);
	GetFont().WriteText(
		GetRenderer(),

		tggd::common::XY<int>(Constants::UI::StatusPanel::BOMBS_TEXT_X,
		Constants::UI::StatusPanel::BOMBS_TEXT_Y),
		ss.str(),
		Constants::Color::WHITE);
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
	SDL_RenderSetClipRect(GetRenderer(), &clipRect);
	DrawMoves();
	DrawKeys();
	DrawWounds();
	DrawArmor();
	DrawDiamonds();
	DrawAttack();
	DrawBombs();
	DrawGameOver();
	SDL_RenderSetClipRect(GetRenderer(), nullptr);
}

void StatusPanelRenderer::DrawMoves() const
{
	std::stringstream ss;
	ss << gameData.GetMoves();
	DrawStatistic
	(
		Constants::UI::StatusPanel::MOVE_ICON_SPRITE_NAME,
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::MOVE_ICON_X,
			Constants::UI::StatusPanel::MOVE_ICON_Y
			),
		ss.str(),
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::MOVE_TEXT_X,
			Constants::UI::StatusPanel::MOVE_TEXT_Y
			)
	);
}

void StatusPanelRenderer::DrawKeys() const
{
	std::stringstream ss;
	ss << gameData.GetHunter()->GetKeys();
	DrawStatistic
	(
		Constants::UI::StatusPanel::KEYS_ICON_SPRITE_NAME,
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::KEYS_ICON_X,
			Constants::UI::StatusPanel::KEYS_ICON_Y
			),
		ss.str(),
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::KEYS_TEXT_X,
			Constants::UI::StatusPanel::KEYS_TEXT_Y
			)
	);
}

void StatusPanelRenderer::DrawWounds() const
{
	std::stringstream ss;
	ss << gameData.GetHunter()->GetHealth() << "/" << gameData.GetHunter()->GetMaximumHealth();
	DrawStatistic
	(
		Constants::UI::StatusPanel::HEALTH_ICON_SPRITE_NAME,
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::HEALTH_ICON_X,
			Constants::UI::StatusPanel::HEALTH_ICON_Y
			),
		ss.str(),
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::HEALTH_TEXT_X,
			Constants::UI::StatusPanel::HEALTH_TEXT_Y
			)
	);
}

void StatusPanelRenderer::DrawArmor() const
{
	std::stringstream ss;
	ss << gameData.GetHunter()->GetArmor() << "/" << gameData.GetHunter()->GetMaximumArmor();
	DrawStatistic
	(
		Constants::UI::StatusPanel::ARMOR_ICON_SPRITE_NAME,
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::ARMOR_ICON_X,
			Constants::UI::StatusPanel::ARMOR_ICON_Y
			),
		ss.str(),
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::ARMOR_TEXT_X,
			Constants::UI::StatusPanel::ARMOR_TEXT_Y
			)
	);
}

void StatusPanelRenderer::DrawAttack() const
{
	std::stringstream ss;
	ss << "1d" << gameData.GetHunter()->GetMaximumAttack();
	DrawStatistic
	(
		Constants::UI::StatusPanel::ATTACK_ICON_SPRITE_NAME,
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::ATTACK_ICON_X,
			Constants::UI::StatusPanel::ATTACK_ICON_Y
		),
		ss.str(),
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::ATTACK_TEXT_X,
			Constants::UI::StatusPanel::ATTACK_TEXT_Y
		)
	);
}

void StatusPanelRenderer::DrawStatistic
(
	const std::string& spriteName, 
	const tggd::common::XY<int>& spriteXY, 
	const std::string& text, 
	const tggd::common::XY<int>& textXY
) const
{
	spriteManager.GetSprite(spriteName)->Draw
	(
		GetRenderer(),
		spriteXY
	);
	GetFont().WriteText(
		GetRenderer(),
		textXY,
		text,
		Constants::Color::WHITE);
}

void StatusPanelRenderer::DrawDiamonds() const
{
	std::stringstream ss;
	ss << gameData.GetHunter()->GetDiamonds();
	DrawStatistic
	(
		Constants::UI::StatusPanel::DIAMOND_ICON_SPRITE_NAME,
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::DIAMOND_ICON_X,
			Constants::UI::StatusPanel::DIAMOND_ICON_Y
		),
		ss.str(),
		tggd::common::XY<int>
		(
			Constants::UI::StatusPanel::DIAMOND_TEXT_X,
			Constants::UI::StatusPanel::DIAMOND_TEXT_Y
		)
	);
}