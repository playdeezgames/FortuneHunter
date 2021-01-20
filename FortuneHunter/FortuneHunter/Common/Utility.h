#pragma once
#include <vector>
#include <string>
namespace tggd::common
{
	class Utility
	{
	public:
		static std::vector<std::string> CommandLineToStringVector(int, char**);
		static void SeedRandomNumberGenerator();
	};
}

