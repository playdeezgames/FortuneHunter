#pragma once
#include <map>
#include <vector>
#include <string>
#include "json.hpp"
#include "Utility.h"
#include "Finisher.h"
#include "FinishManager.h"
template<typename TIdentifer, typename TDescriptor>
class BaseDescriptorManager: public tggd::common::Finisher
{
private:
	std::map<TIdentifer, TDescriptor*> descriptors;
protected:
	virtual TIdentifer ParseKey(const std::string&) = 0;
	virtual TDescriptor* ParseDescriptor(const nlohmann::json&) = 0;
public:
	BaseDescriptorManager(tggd::common::FinishManager& finishManager)
	{
		finishManager.Add(this);
	}
	void Start(const std::string& fileName)
	{
		nlohmann::json j = tggd::common::Utility::LoadJSON(fileName);
		for (auto& item : j.items())
		{
			descriptors[ParseKey(item.key())] =
				ParseDescriptor(item.value());
		}
	}
	void Finish()
	{
		for (auto& entry : descriptors)
		{
			if (entry.second)
			{
				delete entry.second;
				entry.second = nullptr;
			}
		}
	}
	std::vector<TIdentifer> GetTypes() const
	{
		std::vector<TIdentifer> result;
		for (auto& entry : descriptors)
		{
			result.push_back(entry.first);
		}
		return result;

	}
	const TDescriptor* GetDescriptor(TIdentifer identifier) const
	{
		auto iter = descriptors.find(identifier);
		if (iter != descriptors.end())
		{
			return iter->second;
		}
		return nullptr;
	}
};

