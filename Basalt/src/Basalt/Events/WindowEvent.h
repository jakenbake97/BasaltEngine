#pragma once
#include "Event.h"

namespace Basalt
{
	class BASALT_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		static EventType GetStaticType() { return EventType::WindowClose; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "WindowClose"; }
		int GetCategories() const override {return static_cast<int>(EventCategory::Window);}
	};

	class BASALT_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent() = default;

		static EventType GetStaticType() { return EventType::WindowResize; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "WindowResize"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	};

	class BASALT_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		static EventType GetStaticType() { return EventType::WindowFocus; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "WindowFocus"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	};

	class BASALT_API WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() = default;

		static EventType GetStaticType() { return EventType::WindowLostFocus; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "WindowLostFocus"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	};

	class BASALT_API WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent() = default;

		static EventType GetStaticType() { return EventType::WindowMoved; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "WindowMoved"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	};
}
