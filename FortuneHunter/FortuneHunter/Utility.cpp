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
		nlohmann::json document;
		std::ifstream input(fileName);
		if (input.is_open())
		{
			input >> document;
			input.close();
		}
		return document;
	}

	void Utility::SaveJSON(const std::string& fileName, const nlohmann::json& document)
	{
		std::ofstream output(fileName);
		if (output.is_open())
		{
			output << document;
			output.close();
		}
	}


	int Utility::GenerateRandomNumberFromRange(int minimum, int maximum)
	{
		return rand() % (maximum - minimum) + minimum;
	}
}

