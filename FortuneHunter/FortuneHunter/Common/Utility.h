#pragma once
#include <vector>
#include <string>
#include <map>
namespace tggd::common
{
	class Utility
	{
	public:
		static std::vector<std::string> CommandLineToStringVector(int, char**);
		static void SeedRandomNumberGenerator();
		static std::map<std::string, std::string> LoadResourceMap(const std::string&);
	};
}

