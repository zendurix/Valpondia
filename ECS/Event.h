#pragma once

#include "../ECS/ECS_config.h"


class Event
{
private:
	EventType type;

	int value;

public:
	inline bool operator == (const Event& other)
	{
		if (type == other.type && value == other.value)
			return true;
		return false;
	}
	inline bool operator != (const Event& other)
	{
		return (!(*this == other));
	}


	Event(EventType eType, int val) : type(eType), value(val) {}
	~Event() {};


	EventType get_type() const { return type; }
	int get_value()		 const { return value; }

	//void set_type(EventType eType) { type = eType; }
	void set_value(int val)		   { value = val; }

};
	
inline static Event NULL_EVENT = Event{ EventType::placeHolder, -1 };


