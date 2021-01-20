#include "Utility.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
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

	std::map<std::string, std::string> Utility::LoadResourceMap(const std::string& fileName)
	{
		std::map < std::string, std::string> result;
		std::ifstream input(fileName);
		if (input.is_open())
		{
			std::string line;
			while (std::getline(input, line))
			{
				auto position = line.find('=');
				if (position != std::string::npos)
				{
					std::string name = line.substr(0, position);
					std::string fileName = line.substr(position + 1);
					result[name] = fileName;
				}
			}
			input.close();
		}
		return result;
	}
}

