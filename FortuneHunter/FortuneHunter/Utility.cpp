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

	std::vector<std::string> Utility::Tokenize(const std::string& original, char separator)
	{
		std::string input = original;
		std::vector<std::string> result;
		auto position = input.find(separator);
		while (position != std::string::npos)
		{
			auto token = input.substr(0, position);
			if (!token.empty())
			{
				result.push_back(token);
			}
			input = input.substr(position + 1);
			position = input.find(separator);
		}
		if (!input.empty())
		{
			result.push_back(input);
		}
		return result;
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

