#pragma once
#include <vector>
#include <string>
#include <map>
#include "json.hpp"
namespace tggd::common
{
	class Utility
	{
	public:
		static std::vector<std::string> CommandLineToStringVector(int, char**);
		static void SeedRandomNumberGenerator();
		static int GenerateRandomNumberFromRange(int, int);
		static nlohmann::json LoadJSON(const std::string&);
		static int StringToInt(const std::string&);
		template<typename TDelete>
		static void SafeDelete(TDelete*& ptr)
		{
			if (ptr)
			{
				delete ptr;
				ptr = nullptr;
			}
		}
	};
}

