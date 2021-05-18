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
		String GetName() const override { return "Window Close Event"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
		String ToString() const override { return GetName(); }
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

		String ToString() const override{return GetName() + ": Size(" + width + ", " + height + ")";}

		static EventType GetStaticType() { return EventType::WindowResize; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Window Resize Event"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	};

	class BASALT_API WindowFocusEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowFocus; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Window Focus Event"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
		String ToString() const override { return GetName(); }
	};

	class BASALT_API WindowLostFocusEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowLostFocus; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "Window Lost Focus Event"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
		String ToString() const override { return GetName(); }
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
		String GetName() const override { return "Window Moved Event"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
		String ToString() const override { return GetName() + ": Position(" + x + ", " + y + ")"; }
	};
}
