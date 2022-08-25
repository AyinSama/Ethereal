#ifndef _EVENT_MANAGER_HPP_
#define _EVENT_MANAGER_HPP_

#include "Pch.h"

class EventManager {
	SingleObject(EventManager);

public:
	template <class EventType>
	using Handler = std::function<void(const EventType&)>;

	template <class EventType>
	void reg(Handler<EventType> handler) {
		if (EventType::getType() >= this->handlers.size())
			this->handlers.resize(EventType::getType() + 1);
		this->handlers[EventType::getType()].push_back(
			HandlerWrapper<EventType>(handler));
	}
	
	template <class EventType>
	void call(const EventType& event) {
		if (EventType::getType() >= this->handlers.size())
			this->handlers.resize(EventType::getType() + 1);
		for (auto& handler : this->handlers[event.getType()]) {
			handler(event);
		}
	}

	template <class EventType>
	class HandlerWrapper {
	public:
		HandlerWrapper(Handler<EventType> handler) : handler(handler) {}
		void operator()(const AbstractEvent& event) { this->handler(static_cast<const EventType&>(event)); }
		Handler<EventType> handler;
	};

private:
	std::vector<std::vector<Handler<AbstractEvent>>> handlers;

};

#endif // _EVENT_MANAGER_HPP_

