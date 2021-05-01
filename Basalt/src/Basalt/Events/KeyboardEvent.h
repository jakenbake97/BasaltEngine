#pragma once
#include "Event.h"

namespace Basalt
{
	class BASALT_API KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent() = default;

		static EventType GetStaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "KeyPressed"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard);}
	};

	class BASALT_API KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent() = default;

		static EventType GetStaticType() { return EventType::KeyReleased; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "KeyReleased"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard); }
	};
}
