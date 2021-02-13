#include "Statistics.h"
#include "Utility.h"
Statistics::Statistics(const std::string& fileName)
	: fileName(fileName)
	, gamesPlayed(0)
	, totalScore(0)
	, highScore(0)
{

}

const std::string PROPERTY_HIGH_SCORE = "highScore";
const std::string PROPERTY_TOTAL_SCORE = "totalScore";
const std::string PROPERTY_GAMES_PLAYED = "gamesPlayed";

void Statistics::Load() 
{
	auto properties = tggd::common::Utility::LoadJSON(fileName);
	gamesPlayed = properties[PROPERTY_GAMES_PLAYED];
	totalScore = properties[PROPERTY_TOTAL_SCORE];
	highScore = properties[PROPERTY_HIGH_SCORE];
}

void Statistics::Save()
{
	nlohmann::json properties;
	properties[PROPERTY_GAMES_PLAYED] = gamesPlayed;
	properties[PROPERTY_TOTAL_SCORE] = totalScore;
	properties[PROPERTY_HIGH_SCORE] = highScore;
	tggd::common::Utility::SaveJSON(fileName, properties);
}

int Statistics::GetGamesPlayed() const
{
	return gamesPlayed;
}

int Statistics::GetHighScore() const
{
	return highScore;
}

int Statistics::GetAverageScore() const
{
	return (gamesPlayed > 0) ? (totalScore / gamesPlayed) : (0);
}

void Statistics::AddGame(int score)
{
	Load();
	totalScore += score;
	gamesPlayed++;
	highScore = (score > highScore) ? (score) : (highScore);
	Save();
}

