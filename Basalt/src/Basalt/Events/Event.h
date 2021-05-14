#pragma once
#include "BEpch.h"

namespace Basalt
{
	enum class EventType
	{
		None = 0,
		// Window Events
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		// Application Events
		AppTick, AppUpdate, AppRender,
		// Keyboard Events
		KeyPressed, KeyReleased,
		// Mouse Events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, MouseEnter, MouseLeave
	};

	enum class EventCategory
	{
		None			= 0,
		Application		= BIT(0),
		Keyboard		= BIT(1),
		Mouse			= BIT(2),
		Window			= BIT(3)
	};
	
	class BASALT_API Event
	{
		friend class EventDispatcher;
	protected:
		bool handled = false;
	public:
		virtual EventType GetEventType() const { return GetStaticType(); };
		virtual String GetName() const { return "Generic Event"; }
		virtual int GetCategories() const { return static_cast<int>(EventCategory::None);}
		virtual String ToString() const { return GetName(); }
		static EventType GetStaticType() { return EventType::None; }

		bool IsInCategory(EventCategory category) const
		{
			return GetCategories() & static_cast<int> (category);
		}

		virtual ~Event() = default;
	};

	class EventDispatcher
	{
	private:
		template<typename T>
		using EventFunc = std::function<bool(T&)>;

		Event& event;
	public:
		EventDispatcher(Event& event)
			: event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFunc<T> func)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				event.handled = func(*static_cast<T*>(&event));
				return true;
			}
			return false;
		}
	};

	template<typename OStream>
	OStream& operator<<(OStream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
