#pragma once
#include "Event.h"

namespace Basalt
{
	class BASALT_API MouseButtonEvent : public Event
	{
	protected:
		int button;
		MouseButtonEvent(const int button) : button(button) {}
	public:
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
		int GetButton() const { return button; }
	};
	
	class BASALT_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const int button) : MouseButtonEvent(button){}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseButtonPressed"; }
	};

	class BASALT_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const int button) : MouseButtonEvent(button) {}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseButtonReleased"; }
	};

	class BASALT_API MouseScrolledEvent : public Event
	{
	private:
		// TODO: check with mouse input in D3D implementation
		float offset;
	public:
		MouseScrolledEvent(const float scrollOffset) : offset(scrollOffset) {}

		float GetScrollOffset() const { return offset; }
		
		static EventType GetStaticType() { return EventType::MouseScrolled; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseScrolled"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
	};

	class BASALT_API MousePositionEvent : public Event
	{
	protected:
		float x, y;
		MousePositionEvent(const float xPos, const float yPos) : x(xPos), y(yPos) {}

	public:
		float GetX() const { return x; }
		float GetY() const { return y; }

		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
	};
	
	class BASALT_API MouseMovedEvent : public MousePositionEvent
	{
	public:
		MouseMovedEvent(const float xPos, const float yPos) : MousePositionEvent(xPos, yPos) {}

		static EventType GetStaticType() { return EventType::MouseMoved; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseMoved"; }
	};

	class BASALT_API MouseEnterEvent : public MousePositionEvent
	{
	public:
		MouseEnterEvent(const float xPos, const float yPos) : MousePositionEvent(xPos, yPos) {}

		static EventType GetStaticType() { return EventType::MouseEnter; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseEnter"; }
		
	};

	class BASALT_API MouseLeaveEvent : public MousePositionEvent
	{
	public:
		MouseLeaveEvent(const float xPos, const float yPos) : MousePositionEvent(xPos, yPos) {}
		
		static EventType GetStaticType() { return EventType::MouseLeave; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseLeave"; }
	};
}
