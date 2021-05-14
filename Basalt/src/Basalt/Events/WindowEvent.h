#pragma once
#include "Event.h"
#include "Platform/Window.h"

namespace Basalt
{
	class BASALT_API WindowCloseEvent : public Event
	{
	private:
		int code;
	public:
		WindowCloseEvent(const int exitCode) : code(exitCode)
		{
		}

		int GetExitCode() const { return code; }

		static EventType GetStaticType() { return EventType::WindowClose; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "WindowCloseEvent"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	};

	class BASALT_API WindowResizeEvent : public Event
	{
	private:
		unsigned int width, height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width(width), height(height)
		{
		}

		unsigned int GetWidth() const { return width; }
		unsigned int GetHeight() const { return height; }

		String ToString() const override
		{
			String temp("WindowResizeEvent: ");
			temp += std::to_string(width) + ", " + std::to_string(height);
			return temp;
		}

		static EventType GetStaticType() { return EventType::WindowResize; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "WindowResizeEvent"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	};

	class BASALT_API WindowFocusEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowFocus; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "WindowFocusEvent"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	};

	class BASALT_API WindowLostFocusEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowLostFocus; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "WindowLostFocusEvent"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	};

	class BASALT_API WindowMovedEvent : public Event
	{
	private:
		int x, y;

	public:
		WindowMovedEvent(const int xPos, const int yPos) : x(xPos), y(yPos)
		{
		}

		static EventType GetStaticType() { return EventType::WindowMoved; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "WindowMovedEvent"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	};
}
