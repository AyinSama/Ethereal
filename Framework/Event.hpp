#ifndef _EVENT_H_
#define _EVENT_H_

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

#endif // _EVENT_H_

