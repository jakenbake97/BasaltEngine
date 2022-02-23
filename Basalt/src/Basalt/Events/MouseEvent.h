#pragma once
#include "Event.h"
#include "Basalt/MouseCodes.h"

namespace Basalt
{
	/// <summary>
	/// Generic mouse button event that the specific mouse button events inherit from
	/// </summary>
	class MouseButtonEvent : public Event
	{
	protected:
		/// <summary>
		/// Constructs a mouse button event from a mouse button
		/// </summary>
		/// <param name="button">the button to create the event from</param>
		MouseButtonEvent(const MouseCode button) : button(button) {}
	public:
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
		/// <summary>
		/// Gets the mouse button associated with this event
		/// </summary>
		/// <returns>the mouse button</returns>
		MouseCode GetButton() const { return button; }
	protected:
		MouseCode button;
	};
	
	/// <summary>
	/// A mouse button event when the buttons are pressed
	/// </summary>
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		/// <summary>
		/// Constructs a MouseButtonPressedEvent from a specific mouse button
		/// </summary>
		/// <param name="button">the mouse button pressed</param>
		MouseButtonPressedEvent(const MouseCode button) : MouseButtonEvent(button){}

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::MouseButtonPressed</returns>
		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Mouse Button Pressed Event"; }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName() + ": Button[" + button + "]"; }
	};

	/// <summary>
	/// A mouse button event when a button is released
	/// </summary>
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		/// <summary>
		/// Constructs a MouseButtonReleased event from a specific keycode
		/// </summary>
		/// <param name="button">The mouse button that was released</param>
		MouseButtonReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {}

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::MouseButtonReleased</returns>
		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Mouse Button Released Event"; }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName() + ": Button[" + button + "]"; }
	};

	/// <summary>
	/// Event when the mouse scroll wheel is moved
	/// </summary>
	class MouseScrolledEvent : public Event
	{
	public:
		/// <summary>
		/// Constructs a MouseScrolled event with the amount that the scroll wheel was moved
		/// </summary>
		/// <param name="scrollOffset">the amount the scroll wheel was moved</param>
		MouseScrolledEvent(const int scrollOffset) : offset(scrollOffset) {}

		/// <summary>
		/// Gets the amount that the scroll wheel was moved
		/// </summary>
		/// <returns>The scroll wheel offset amount</returns>
		int GetScrollOffset() const { return offset; }

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::MouseScrolled</returns>
		static EventType GetStaticType() { return EventType::MouseScrolled; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Mouse Scrolled Event"; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName() + ": Scroll Offset[" + offset + "]"; }
	private:
		int offset;
	};

	/// <summary>
	/// Generic mouse position event
	/// </summary>
	class MousePositionEvent : public Event
	{
	protected:
		/// <summary>
		/// Constructs a MousePosition event for any events related to mouse position
		/// </summary>
		/// <param name="position">the current position of the mouse</param>
		MousePositionEvent(const Vector2Int position) :pos(position) {}

	public:
		/// <summary>
		/// Returns the x component of the mouse position
		/// </summary>
		/// <returns>x position</returns>
		int GetX() const { return pos.x; }
		/// <summary>
		/// Returns the y component of the mouse position
		/// </summary>
		/// <returns>y position</returns>
		int GetY() const { return pos.y; }
		/// <summary>
		/// gets the mouse position for the event
		/// </summary>
		/// <returns>mouse position</returns>
		Vector2Int GetPosition() const { return pos; }

		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
	protected:
		Vector2Int pos;
	};
	
	/// <summary>
	/// Event that is created whenever the mouse moves
	/// </summary>
	class MouseMovedEvent : public MousePositionEvent
	{
	public:
		/// <summary>
		/// Constructs a MouseMoved event whenever the mouse moves
		/// </summary>
		/// <param name="position">The current position of the mouse</param>
		MouseMovedEvent(const Vector2Int position) : MousePositionEvent(position) {}

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::MouseMoved</returns>
		static EventType GetStaticType() { return EventType::MouseMoved; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Mouse Moved Event"; }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName() + ": Position(" + pos.x +", " + pos.y + ")"; }
	};

	/// <summary>
	/// Event for when the mouse enters the window
	/// </summary>
	class MouseEnterEvent : public MousePositionEvent
	{
	public:
		/// <summary>
		/// Constructs a MouseEnter event with the current position of the mouse when it enters the window
		/// </summary>
		/// <param name="position">The position of the mouse when it entered the window</param>
		MouseEnterEvent(const Vector2Int position) : MousePositionEvent(position) {}

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::MouseEnter</returns>
		static EventType GetStaticType() { return EventType::MouseEnter; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Mouse Enter Event"; }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName() + ": Position(" + pos.x + ", " + pos.y + ")"; }
	};

	/// <summary>
	/// Event for when the mouse leaves the window
	/// </summary>
	class MouseLeaveEvent : public MousePositionEvent
	{
	public:
		/// <summary>
		/// Constructs a MouseLeave event with the current position of the mouse when it leaves the window
		/// </summary>
		/// <param name="position">the last position of the mouse when it left the window</param>
		MouseLeaveEvent(const Vector2Int position) : MousePositionEvent(position) {}

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::MouseLeave</returns>
		static EventType GetStaticType() { return EventType::MouseLeave; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Mouse Leave Event"; }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName() + ": Position(" + pos.x + ", " + pos.y + ")"; }
	};
}
