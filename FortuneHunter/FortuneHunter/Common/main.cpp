#include "Application.h"
#include <stdlib.h>
#include <time.h>

static std::vector<std::string> CommandLineToStringVector(int argc, char** argv)
{
	std::vector<std::string> arguments(argc);
	for (int index = 0; index < argc; ++index)
	{
		arguments.push_back(std::string(argv[index]));
	}
	return arguments;
}

static void SeedRandomNumberGenerator()
{
	srand((unsigned int)time(nullptr));
}

int main(int argc, char** argv)
{
	SeedRandomNumberGenerator();
	auto arguments = CommandLineToStringVector(argc, argv);
	return tggd::common::Application::Run(arguments);
}