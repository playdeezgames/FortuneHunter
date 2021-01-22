#pragma once
#include "CommandProcessor.h"
#include <map>
namespace tggd::common
{
	template<typename TIdentifier, typename TCommand>
	class CommandProcessorManager : CommandProcessor<TCommand>
	{
	private:
		std::map<TIdentifier, CommandProcessor<TCommand>*> commandProcessors;
		const TIdentifier& current;
	public:
		CommandProcessorManager(const TIdentifier& current)
			: commandProcessors()
			, current(current)
		{

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
					delete entry.second;
					entry.second = nullptr;
				}
			}
			commandProcessors.clear();
		}
	};
}

