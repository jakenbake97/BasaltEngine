#pragma once
#include "Event.h"

namespace Basalt
{
	class BASALT_API KeyEvent : public Event
	{
	protected:
		int keycode;
		
		KeyEvent(const int keycode) : keycode(keycode) {}

	public:
		int GetKeyCode() const { return keycode; }

		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard); }
	};
	
	class BASALT_API KeyPressedEvent final : public KeyEvent
	{
	private:
		int repeatCount;
		
	public:
		KeyPressedEvent(const int keycode, const int repeatCount) : KeyEvent(keycode), repeatCount(repeatCount) {}

		static EventType GetStaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "KeyPressed"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard);}

		String ToString() const override
		{
			return { "KeyPressedEvent: " + std::to_string(keycode) + " (" + std::to_string(repeatCount) + " repeats)" };
		}
	};

	class BASALT_API KeyReleasedEvent final : public KeyEvent
	{
	public:
		KeyReleasedEvent(const int keycode) : KeyEvent(keycode) {}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "KeyReleased"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard); }
	};
}
