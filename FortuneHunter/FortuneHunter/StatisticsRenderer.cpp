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
	GetFont().WriteText(GetRenderer(), tggd::common::XY(0, 0), "Statistics:", Constants::Color::GREEN);

	std::stringstream ss;
	ss << "Games Played: " << statistics.GetGamesPlayed();
	GetFont().WriteText(GetRenderer(), tggd::common::XY(0, 32), ss.str(), Constants::Color::GRAY);

	ss.str("");
	ss << "High Score: " << statistics.GetHighScore();
	GetFont().WriteText(GetRenderer(), tggd::common::XY(0, 64), ss.str(), Constants::Color::GRAY);

	ss.str("");
	ss << "Average Score: " << statistics.GetAverageScore();
	GetFont().WriteText(GetRenderer(), tggd::common::XY(0, 96), ss.str(), Constants::Color::GRAY);

}
