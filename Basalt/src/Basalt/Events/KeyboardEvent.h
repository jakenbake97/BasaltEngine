#pragma once
#include "Event.h"
#include "Basalt/Keycodes.h"

namespace Basalt
{
	class BASALT_API KeyEvent : public Event
	{
	protected:
		KeyCode keycode;
		
		KeyEvent(const KeyCode keycode) : keycode(keycode) {}

	public:
		int GetKeyCode() const { return keycode; }

		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard); }
	};
	
	class BASALT_API KeyPressedEvent final : public KeyEvent
	{
	private:
		int repeatCount;
		
	public:
		KeyPressedEvent(const KeyCode keycode, const int repeatCount) : KeyEvent(keycode), repeatCount(repeatCount) {}

		static EventType GetStaticType() { return EventType::KeyPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Key Pressed Event"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard);}

		String ToString() const override
		{
			return GetName() + ": " + keycode + " " + Key::GetKeyName.at(keycode) +" (" + repeatCount + " repeats)";
		}
	};

	class BASALT_API KeyReleasedEvent final : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Key Released Event"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard); }

		String ToString() const override { return GetName() + ": " + keycode + " " + Key::GetKeyName.at(keycode); }
	};
}
