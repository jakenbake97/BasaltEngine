#pragma once
#include "Event.h"
#include "Basalt/MouseCodes.h"

namespace Basalt
{
	class BASALT_API MouseButtonEvent : public Event
	{
	protected:
		MouseCode button;
		MouseButtonEvent(const MouseCode button) : button(button) {}
	public:
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
		MouseCode GetButton() const { return button; }
	};
	
	class BASALT_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button) : MouseButtonEvent(button){}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Mouse Button Pressed Event"; }
		String ToString() const override { return GetName() + ": Button[" + button + "]"; }
	};

	class BASALT_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Mouse Button Released Event"; }
		String ToString() const override { return GetName() + ": Button[" + button + "]"; }
	};

	class BASALT_API MouseScrolledEvent : public Event
	{
	private:
		float offset;
	public:
		MouseScrolledEvent(const float scrollOffset) : offset(scrollOffset) {}

		float GetScrollOffset() const { return offset; }
		
		static EventType GetStaticType() { return EventType::MouseScrolled; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Mouse Scrolled Event"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
		String ToString() const override { return GetName() + ": Scroll Offset[" + offset + "]"; }
	};

	class BASALT_API MousePositionEvent : public Event
	{
	protected:
		int x, y;
		MousePositionEvent(const int xPos, const int yPos) : x(xPos), y(yPos) {}

	public:
		int GetX() const { return x; }
		int GetY() const { return y; }
		std::pair<int, int> GetPosition() { return {x,y}; }

		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
	};
	
	class BASALT_API MouseMovedEvent : public MousePositionEvent
	{
	public:
		MouseMovedEvent(const int xPos, const int yPos) : MousePositionEvent(xPos, yPos) {}

		static EventType GetStaticType() { return EventType::MouseMoved; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Mouse Moved Event"; }
		String ToString() const override { return GetName() + ": Position(" + x +", " + y + ")"; }
	};

	class BASALT_API MouseEnterEvent : public MousePositionEvent
	{
	public:
		MouseEnterEvent(const float xPos, const float yPos) : MousePositionEvent(xPos, yPos) {}

		static EventType GetStaticType() { return EventType::MouseEnter; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Mouse Enter Event"; }
		String ToString() const override { return GetName() + ": Position(" + x + ", " + y + ")"; }
	};

	class BASALT_API MouseLeaveEvent : public MousePositionEvent
	{
	public:
		MouseLeaveEvent(const float xPos, const float yPos) : MousePositionEvent(xPos, yPos) {}
		
		static EventType GetStaticType() { return EventType::MouseLeave; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Mouse Leave Event"; }
		String ToString() const override { return GetName() + ": Position(" + x + ", " + y + ")"; }
	};
}
