#pragma once
#include "EventHandler.h"
#include <map>
namespace tggd::common
{
	template<typename TIdentifier>
	class EventHandlerManager : EventHandler
	{
	private:
		std::map<TIdentifier, EventHandler*> eventHandlers;
		const TIdentifier& current;
	public:
		EventHandlerManager(const TIdentifier& current)
			: eventHandlers()
			, current(current)
		{

		}
		void AddEventHandler(const TIdentifier& identifier, EventHandler* eventHandler)
		{
			eventHandlers[identifier] = eventHandler;
		}
		bool OnEvent(const SDL_Event& evt)
		{
			auto iter = eventHandlers.find(current);
			if (iter != eventHandlers.end())
			{
				return iter->second->OnEvent(evt);
			}
			return true;
		}
		void Finish()
		{
			for (auto& entry : eventHandlers)
			{
				if (entry.second)
				{
					delete entry.second;
					entry.second = nullptr;
				}
			}
			eventHandlers.clear();
		}
	};
}

