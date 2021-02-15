#include "FinalScoreRenderer.h"
#include "ColorConstants.h"
#include "HunterAward.h"
#include <sstream>
FinalScoreRenderer::FinalScoreRenderer
(
	SDL_Renderer* renderer, 
	const tggd::common::SpriteFont& romFont, 
	const tggd::common::Sprite* background,
	const GameData& gameData
)
	: BaseMenuRenderer(renderer, romFont, background)
	, gameData(gameData)
{

}

void FinalScoreRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
	//TODO: magic numbers vvv
	GetFont().WriteText(GetRenderer(), tggd::common::XY(0, 0), "Final Score:", Constants::Color::GREEN);

	int y = 32;//TODO: magic number!
	for (auto award : HunterAwardHelper::GetAll())
	{
		std::stringstream ss;
		ss << HunterAwardHelper::GetName(award) << " x" << gameData.GetHunter()->GetTally(award) << " -> " << gameData.GetHunter()->GetScore(award);//TODO: magic strings
		GetFont().WriteText(GetRenderer(), tggd::common::XY(0, y), ss.str(), Constants::Color::GRAY);
		y += 16;//TODO: magic number
	}
	y += 16;//TODO: MAGIC
	std::stringstream ss;
	ss << "Final Score: " << gameData.GetHunter()->GetScore();
	GetFont().WriteText(GetRenderer(), tggd::common::XY(0, y), ss.str(), Constants::Color::CYAN);
}
