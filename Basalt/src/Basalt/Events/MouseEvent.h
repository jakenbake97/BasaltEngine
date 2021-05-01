#pragma once
#include "Event.h"

namespace Basalt
{
	class BASALT_API MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent() = default;

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseButtonPressed"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
	};

	class BASALT_API MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent() = default;

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseButtonReleased"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
	};

	class BASALT_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent() = default;

		static EventType GetStaticType() { return EventType::MouseMoved; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseMoved"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
	};

	class BASALT_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent() = default;

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseScrolled"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
	};

	class BASALT_API MouseEnterEvent : public Event
	{
	public:
		MouseEnterEvent() = default;

		static EventType GetStaticType() { return EventType::MouseEnter; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseEnter"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
	};

	class BASALT_API MouseLeaveEvent : public Event
	{
	public:
		MouseLeaveEvent() = default;

		static EventType GetStaticType() { return EventType::MouseLeave; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "MouseLeave"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Mouse); }
	};
}
