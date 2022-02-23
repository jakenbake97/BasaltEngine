#pragma once

#include "Event.h"

namespace Basalt
{
	/// <summary>
	/// Event dispatched every update loop tick of the application class
	/// </summary>
	class AppTickEvent : public Event
	{
	public:
		/// <summary>
		/// Constructs an AppTickEvent and takes the amount of time from the last update tick to now
		/// </summary>
		/// <param name="deltaTime">the difference in time between the last update tick and now</param>
		AppTickEvent(const float deltaTime) : deltaTime(deltaTime) {}

		/// <summary>
		/// Gets the amount of time since the last app update
		/// </summary>
		/// <returns>the deltaTime from last update to now</returns>
		float GetDeltaTime() const { return deltaTime; }
		
		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>enum EventType::AppTick</returns>
		static EventType GetStaticType() { return EventType::AppTick; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "App Tick Event"; }
		/// <summary>
		/// Converts the event name and data to a string
		/// </summary>
		/// <returns>a string formatted as {eventName memberName: memberValue}</returns>
		String ToString() const override { return GetName() + " DeltaTime: " + deltaTime; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Application);}
	private:
		float deltaTime;
	};

	/// <summary>
	/// Event dispatched after a frame was rendered
	/// </summary>
	class AppRenderEvent : public Event
	{
	public:
		/// <summary>
		/// Constructs an AppRenderEvent
		/// </summary>
		AppRenderEvent() = default;
		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>enum EventType::AppRender</returns>
		static EventType GetStaticType() { return EventType::AppRender; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "App Render Event"; }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns></returns>
		String ToString() const override { return GetName(); }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Application);}
	};

	/// <summary>
	/// Event dispatched when the application is quitting and should shut down
	/// </summary>
	class AppQuitEvent : public Event
	{
	public:
		/// <summary>
		/// Constructs an AppQuitEvent with a specified exit code to indicate success or error
		/// </summary>
		/// <param name="exitCode">the code posted by the application indicating success or error</param>
		AppQuitEvent(const int exitCode) : code(exitCode) {}

		/// <summary>
		/// Gets the exit code that was posted when the application began to quit
		/// </summary>
		/// <returns>the exit code associated with the event</returns>
		int GetExitCode() const { return code; }

		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>enum EventType::AppQuit</returns>
		static EventType GetStaticType() { return EventType::AppQuit; }
		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		EventType GetEventType() const override { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		String GetName() const override { return "App Quit Event"; }
		/// <summary>
		/// Converts the event to a string
		/// </summary>
		/// <returns>the string containing the event name and it's data</returns>
		String ToString() const override { return GetName() + L" Exit Code: " + code; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		int GetCategories() const override { return static_cast<int>(EventCategory::Application); }
	private:
		int code;
	};
}
