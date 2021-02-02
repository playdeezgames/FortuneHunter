#pragma once
#include <map>
#include "Sprite.h"
#include <string>
#include "SpriteManager.h"
#include "json.hpp"
#include "Utility.h"
#include "FinishManager.h"
namespace tggd::common
{
	template<typename TIdentifier>
	class SpriteTable : public Finisher
	{
	private:
		std::map<TIdentifier, const Sprite*> table;
	protected:
		virtual TIdentifier StringToIdentifier(const std::string&) = 0;
	public:
		SpriteTable(FinishManager& finishManager) :table() 
		{
			finishManager.Add(this);
		}
		void Start(const SpriteManager& spriteManager, const std::string& fileName)
		{
			nlohmann::json j = Utility::LoadJSON(fileName);
			for (auto& entry : j.items())
			{
				TIdentifier identifier = StringToIdentifier(entry.key());
				table[identifier] = spriteManager.GetSprite(entry.value());
			}
		}
		const Sprite* Get(const TIdentifier& identifier) const
		{
			auto iter = table.find(identifier);
			if (iter != table.end())
			{
				return iter->second;
			}
			return nullptr;
		}
		void Finish()
		{
			table.clear();
		}

	};
}

