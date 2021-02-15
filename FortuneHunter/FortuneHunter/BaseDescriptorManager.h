#pragma once
#include <map>
#include <vector>
#include <string>
#include "json.hpp"
#include "Utility.h"
#include "Finisher.h"
#include "FinishManager.h"
#include "Utility.h"
namespace tggd::common
{
	template<typename TIdentifer, typename TDescriptor>
	class BaseDescriptorManager : public tggd::common::Finisher
	{
	private:
		std::map<TIdentifer, TDescriptor*> descriptors;
		std::vector<TIdentifer> identifiers;
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
			nlohmann::json properties = tggd::common::Utility::LoadJSON(fileName);
			for (auto& item : properties.items())
			{
				auto identifier = ParseKey(item.key());
				identifiers.push_back(identifier);
				descriptors[identifier] =
					ParseDescriptor(item.value());
			}
		}
		void Finish()
		{
			tggd::common::Utility::SafeDeleteMap(descriptors);
		}
		const std::vector<TIdentifer>& GetTypes() const
		{
			return identifiers;
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
}