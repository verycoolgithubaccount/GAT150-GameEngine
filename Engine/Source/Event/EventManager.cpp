#include "EventManager.h"

void EventManager::AddObserver(const id_t& id, Observer* observer, EventHandler eventHandler)
{
	Dispatcher dispatcher;
	dispatcher.observer = observer;
	dispatcher.eventHandler = eventHandler;

	m_dispatchers[id].push_back(dispatcher);
}

void EventManager::RemoveObserver(Observer* observer)
{
	for (auto& element : m_dispatchers)
	{
		auto& dispatchers = element.second;
		std::erase_if(dispatchers, [observer](auto& dispatcher) { return dispatcher.observer == observer; }); 
		// in the dispatchers, find the observer of each dispatcher, and delete the one that's the one it's looking for
	}
}

void EventManager::Notify(const Event& event)
{
	auto iter = m_dispatchers.find(event.id); // find the key/value pair where the key is the event id
	if (iter != m_dispatchers.end()) // if the event exists
	{
		auto& dispatchers = iter->second; // ->first is key, ->second is value, this returns the list of dispatchers for the event
		for (auto& dispatcher : dispatchers)
		{
			dispatcher.eventHandler(event);
		}
	}
}
