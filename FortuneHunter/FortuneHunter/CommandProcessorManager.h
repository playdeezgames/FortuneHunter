#pragma once
#include "CommandProcessor.h"
#include <map>
#include "FinishManager.h"
#include "Utility.h"
namespace tggd::common
{
	template<typename TIdentifier, typename TCommand>
	class CommandProcessorManager 
		: public CommandProcessor<TCommand>
		, public Finisher
	{
	private:
		std::map<TIdentifier, CommandProcessor<TCommand>*> commandProcessors;
		const TIdentifier& current;
	public:
		CommandProcessorManager(const TIdentifier& current, FinishManager& finishManager)
			: commandProcessors()
			, current(current)
		{
			finishManager.Add(this);
		}
		void AddCommandProcessor(const TIdentifier& identifier, CommandProcessor<TCommand>* commandProcessor)
		{
			commandProcessors[identifier] = commandProcessor;
		}
		void OnCommand(const TCommand& command)
		{
			auto iter = commandProcessors.find(current);
			if (iter != commandProcessors.end())
			{
				iter->second->OnCommand(command);
			}
		}
		void Finish()
		{
			for (auto& entry : commandProcessors)
			{
				if (entry.second)
				{
					Utility::SafeDelete(entry.second);
				}
			}
			commandProcessors.clear();
		}
	};
}

