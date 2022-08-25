#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include "Pch.h"

abstract_class AbstractEvent {

public:
	inline static unsigned int typeCount = 0;
	virtual ~AbstractEvent() = default;

};

template <class EventType>
class Event : public AbstractEvent {

public:
	static unsigned int getType() {
		static unsigned int etype = AbstractEvent::typeCount++;
		return etype;
	}

};

#endif // _EVENT_HPP_

