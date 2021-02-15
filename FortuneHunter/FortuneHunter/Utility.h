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
		static void SaveJSON(const std::string&, const nlohmann::json&);
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
		template<typename TIdentifier, typename TDelete>
		static void SafeDeleteMap(std::map<TIdentifier, TDelete*>& table)
		{
			for (auto& entry : table)
			{
				if (entry.second)
				{
					SafeDelete(entry.second);
				}
			}
			table.clear();
		}
	};
}

