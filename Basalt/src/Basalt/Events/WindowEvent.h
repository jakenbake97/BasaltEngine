#pragma once
#include "Event.h"
#include "Basalt/Window.h"

namespace Basalt
{
	/// <summary>
	/// Event notifying that the window should close
	/// </summary>
	class WindowCloseEvent : public Event
	{
	public:
		/// <summary>
		/// Constructs the WindowClose event with the program's exit code
		/// </summary>
		/// <param name="exitCode">code indicating success or failure of the program on exit</param>
		WindowCloseEvent(const int exitCode) : code(exitCode){}

		/// <summary>
		/// Gets the exit code for the close event
		/// </summary>
		/// <returns>the exit code value</returns>
		int GetExitCode() const { return code; }

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::WindowClose</returns>
		static EventType GetStaticType() { return EventType::WindowClose; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Window Close Event"; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName(); }
	private:
		int code;
	};

	/// <summary>
	/// Event when the application window resizes 
	/// </summary>
	class WindowResizeEvent : public Event
	{
	public:
		/// <summary>
		/// Constructs a WindowResize event with the new dimensions of the window
		/// </summary>
		/// <param name="width">the new window width</param>
		/// <param name="height">the new window height</param>
		WindowResizeEvent(const uint32 width, const uint32 height)
			: width(width), height(height){}

		/// <summary>
		/// Gets the new width of the window
		/// </summary>
		/// <returns>window width value</returns>
		uint32 GetWidth() const { return width; }
		/// <summary>
		/// Gets the new height of the window
		/// </summary>
		/// <returns>window height value</returns>
		uint32 GetHeight() const { return height; }

		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override{return GetName() + ": Size(" + width + ", " + height + ")";}
		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::KeyReleased</returns>
		static EventType GetStaticType() { return EventType::WindowResize; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Window Resize Event"; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
	private:
		unsigned int width, height;
	};

	/// <summary>
	/// Event when the window is focused
	/// </summary>
	class WindowFocusEvent : public Event
	{
	public:
		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::WindowFocus</returns>
		static EventType GetStaticType() { return EventType::WindowFocus; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Window Focus Event"; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName(); }
	};

	/// <summary>
	/// Event for when the window loses focus
	/// </summary>
	class WindowLostFocusEvent : public Event
	{
	public:
		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::KeyPressed</returns>
		static EventType GetStaticType() { return EventType::WindowLostFocus; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Window Lost Focus Event"; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName(); }
	};

	/// <summary>
	/// Event when the window is moved
	/// </summary>
	class WindowMovedEvent : public Event
	{
	public:
		/// <summary>
		/// Constructs a WindowMoved event with the window's new position
		/// </summary>
		/// <param name="position">The new position of the window</param>
		WindowMovedEvent(const Vector2Int position) : pos(position){}

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>EventType::KeyPressed</returns>
		static EventType GetStaticType() { return EventType::WindowMoved; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "Window Moved Event"; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Window); }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName() + ": Position(" + pos.x + ", " + pos.y + ")"; }
	private:
		Vector2Int pos;
	};
}
