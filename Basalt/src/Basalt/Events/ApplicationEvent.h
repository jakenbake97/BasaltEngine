#pragma once

#include "Event.h"

namespace Basalt
{
	class BASALT_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		static EventType GetStaticType() { return EventType::AppTick; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "AppTick"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Application);}
	};

	class BASALT_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		static EventType GetStaticType() { return EventType::AppUpdate; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "AppUpdate"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Application); }
	};

	class BASALT_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		static EventType GetStaticType() { return EventType::AppRender; }
		EventType GetEventType() const override { return GetStaticType(); }
		String GetName() const override { return "AppRender"; }
		int GetCategories() const override { return static_cast<int>(EventCategory::Application);}
	};
}
