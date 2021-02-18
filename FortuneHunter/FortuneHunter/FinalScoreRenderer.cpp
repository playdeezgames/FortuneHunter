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
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(324, 100), "==Final Score==", Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(320, 96), "==Final Score==", Constants::Color::GREEN);

	int y = 192;//TODO: magic number!
	for (auto award : HunterAwardHelper::GetAll())
	{
		std::stringstream ss;
		ss << HunterAwardHelper::GetName(award) << " x" << gameData.GetHunter()->GetTally(award) << " -> " << gameData.GetHunter()->GetScore(award);//TODO: magic strings
		GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(324, y+4), ss.str(), Constants::Color::BLACK);
		GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(320, y), ss.str(), Constants::Color::GRAY);
		y += 24;//TODO: magic number
	}
	y += 32;//TODO: MAGIC
	std::stringstream ss;
	ss << "Total Score: " << gameData.GetHunter()->GetScore();
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(324, y+4), ss.str(), Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(320, y), ss.str(), Constants::Color::CYAN);
}
