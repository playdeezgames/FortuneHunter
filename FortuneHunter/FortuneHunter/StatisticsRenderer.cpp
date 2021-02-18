#include "StatisticsRenderer.h"
#include "ColorConstants.h"
#include <sstream>
StatisticsRenderer::StatisticsRenderer
(
	SDL_Renderer* renderer,
	const tggd::common::SpriteFont& romFont,
	const tggd::common::Sprite* background,
	const Statistics& statistics
)
	: BaseMenuRenderer(renderer, romFont, background)
	, statistics(statistics)
{

}

void StatisticsRenderer::Draw() const
{
	BaseMenuRenderer::Draw();
	//TODO: magic numbers and string galore!
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(324, 100), "==Statistics==", Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(320, 96), "==Statistics==", Constants::Color::GREEN);

	std::stringstream ss;
	ss << "Games Played: " << statistics.GetGamesPlayed();
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(324, 212), ss.str(), Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(320, 208), ss.str(), Constants::Color::GRAY);

	ss.str("");
	ss << "High Score: " << statistics.GetHighScore();
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(324, 244), ss.str(), Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(320, 240), ss.str(), Constants::Color::GRAY);

	ss.str("");
	ss << "Average Score: " << statistics.GetAverageScore();
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(324, 276), ss.str(), Constants::Color::BLACK);
	GetFont().WriteTextCentered(GetRenderer(), tggd::common::XY(320, 272), ss.str(), Constants::Color::GRAY);

}
