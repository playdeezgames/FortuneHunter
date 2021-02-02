#include "Utility.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
namespace tggd::common
{
	std::vector<std::string> Utility::CommandLineToStringVector(int argc, char** argv)
	{
		std::vector<std::string> arguments(argc);
		for (int index = 0; index < argc; ++index)
		{
			arguments.push_back(std::string(argv[index]));
		}
		return arguments;
	}

	void Utility::SeedRandomNumberGenerator()
	{
		srand((unsigned int)time(nullptr));
	}

	int Utility::StringToInt(const std::string& text)
	{
		std::stringstream ss;
		ss.str(text);
		int result = 0;
		ss >> result;
		return result;
	}

	nlohmann::json Utility::LoadJSON(const std::string& fileName)
	{
		nlohmann::json j;
		std::ifstream input(fileName);
		if (input.is_open())
		{
			input >> j;
			input.close();
		}
		return j;
	}

	int Utility::GenerateRandomNumberFromRange(int minimum, int maximum)
	{
		return rand() % (maximum - minimum) + minimum;
	}
}

