#pragma once
#include <string>
class Statistics
{
private:
	std::string fileName;
	int totalScore;
	int highScore;
	int gamesPlayed;
public:
	Statistics(const std::string&);
	void Load();
	void Save();
	int GetGamesPlayed() const;
	int GetHighScore() const;
	int GetAverageScore() const;
	void AddGame(int);
};