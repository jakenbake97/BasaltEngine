#pragma once

#include "Event.h"

namespace Basalt
{
	class BASALT_API AppTickEvent : public Event
	{
	private:
		float deltaTime;
	public:
		AppTickEvent(const float deltaTime) : deltaTime(deltaTime) {}

		float GetDeltaTime() const { return deltaTime; }
		
		static EventType GetStaticType() { return EventType::AppTick; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "App Tick Event"; }
		String ToString() const override { return GetName() + L" DeltaTime: " + deltaTime; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Application);}
	};

	class BASALT_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		static EventType GetStaticType() { return EventType::AppUpdate; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "App Update Event"; }
		String ToString() const override { return GetName(); }
		int GetCategories() const override { return static_cast<int>(EventCategory::Application); }
	};

	class BASALT_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		static EventType GetStaticType() { return EventType::AppRender; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "App Render Event"; }
		String ToString() const override { return GetName(); }
		int GetCategories() const override { return static_cast<int>(EventCategory::Application);}
	};

	class BASALT_API AppQuitEvent : public Event
	{
	private:
		int code;
	public:
		AppQuitEvent(const int exitCode) : code(exitCode) {}

		int GetExitCode() const { return code; }

		static EventType GetStaticType() { return EventType::AppQuit; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "App Quit Event"; }
		String ToString() const override { return GetName() + L" Exit Code: " + code; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Application); }
	};
}
