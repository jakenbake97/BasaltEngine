#pragma once
#include "Event.h"
#include "Basalt/Keycodes.h"

namespace Basalt
{
	/// <summary>
	/// Generic Key Event that the specific key events inherit from
	/// </summary>
	class KeyEvent : public Event
	{
	protected:
		/// <summary>
		/// Constructs a key event from a key code
		/// </summary>
		/// <param name="keycode">the key to create an event from</param>
		KeyEvent(const KeyCode keycode) : keycode(keycode) {}
	public:
		/// <summary>
		/// Gets the key code associated with this event
		/// </summary>
		/// <returns>the key code</returns>
		int GetKeyCode() const { return keycode; }

		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard); }
	protected:
		KeyCode keycode;
	};

	/// <summary>
	/// A key event when keys are pressed
	/// </summary>
	class KeyPressedEvent final : public KeyEvent
	{
	public:
		/// <summary>
		/// Constructs a KeyPressedEvent from a specific keycode and a count indicating if this key is being held and down and how long
		/// </summary>
		/// <param name="keycode">the key that was pressed</param>
		/// <param name="repeatCount">how long the key has been held</param>
		KeyPressedEvent(const KeyCode keycode, const int repeatCount) : KeyEvent(keycode), repeatCount(repeatCount) {}

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::KeyPressed</returns>
		static EventType GetStaticType() { return EventType::KeyPressed; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Key Pressed Event"; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard);}
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override
		{
			return GetName() + ": " + keycode + " " + Key::GetKeyName.at(keycode) +" (" + repeatCount + " repeats)";
		}
	private:
		int repeatCount;
	};

	/// <summary>
	/// A key event when a key is released
	/// </summary>
	class KeyReleasedEvent final : public KeyEvent
	{
	public:
		/// <summary>
		/// Constructs a KeyReleased event from a specific keycode
		/// </summary>
		/// <param name="keycode">The key that was released</param>
		KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::KeyReleased</returns>
		static EventType GetStaticType() { return EventType::KeyReleased; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Key Released Event"; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Keyboard); }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName() + ": " + keycode + " " + Key::GetKeyName.at(keycode); }
	};
}
