#pragma once
#include <vector>
#include <string>
#include <map>
#include "..\json.hpp"
namespace tggd::common
{
	class Utility
	{
	public:
		static std::vector<std::string> CommandLineToStringVector(int, char**);
		static void SeedRandomNumberGenerator();
		static nlohmann::json LoadJSON(const std::string&);
		static std::vector<std::string> Tokenize(const std::string&, char);
		static int StringToInt(const std::string&);
	};
}

