#pragma once
#include "BEpch.h"

namespace Basalt
{
	/// <summary>
	/// The specific type of event, each event will only have one type
	/// </summary>
	enum class EventType
	{
		None = 0,
		// Application Events
		AppTick,
		AppRender,
		AppQuit,
		// Keyboard Events
		KeyPressed,
		KeyReleased,
		// Mouse Events
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled,
		MouseEnter,
		MouseLeave,
		// Window Events
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved
	};

	/// <summary>
	/// The broader category that the event type belongs to. An event can belong to more than one category
	/// </summary>
	enum class EventCategory
	{
		None = 0,
		Application = BIT(0),
		Keyboard = BIT(1),
		Mouse = BIT(2),
		Window = BIT(3)
	};

	/// <summary>
	/// The generic event class that all specific events inherit from
	/// </summary>
	class Event
	{
		friend class EventDispatcher;
	public:
		Event() = default;
		Event(const Event& other) = default;
		Event(Event&& other) noexcept = default;
		Event& operator=(const Event& other) = default;
		Event& operator=(Event&& other) noexcept = default;
		virtual ~Event() = default;

		/// <summary>
		/// Gets the type of the current event
		/// </summary>
		/// <returns>an EventType enum to the type of event this is</returns>
		virtual EventType GetEventType() const { return GetStaticType(); }
		/// <summary>
		/// Get the name of this specific event
		/// </summary>
		/// <returns>the name of this type of event</returns>
		virtual String GetName() const { return "Generic Event"; }
		/// <summary>
		/// returns the enum categories that this event belongs to
		/// </summary>
		/// <returns>an integer indicating the event categories</returns>
		virtual int GetCategories() const { return static_cast<int>(EventCategory::None); }
		/// <summary>
		/// Converts the event name and data to a string
		/// </summary>
		/// <returns>a string formatted as {eventName memberName: memberValue}</returns>
		virtual String ToString() const { return GetName(); }
		/// <summary>
		/// Returns the type of the event
		/// </summary>
		/// <returns>enum EventType::None</returns>
		static EventType GetStaticType() { return EventType::None; }
		/// <summary>
		/// Checks if this event is in a specific category
		/// </summary>
		/// <param name="category">The category to check if the event belongs to</param>
		/// <returns>a bool indicating if the event belongs to the category</returns>
		bool IsInCategory(EventCategory category) const
		{
			return GetCategories() & static_cast<int>(category);
		}

		/// <summary>
		/// Checks if the event has been handled yet
		/// </summary>
		/// <returns>a bool indicating if the event has been handled</returns>
		bool IsHandled() const
		{
			return handled;
		}

	private:
		bool handled = false;
	};

	/// <summary>
	/// Handles events by dispatching them to a provided function if it matches the templated event type
	/// </summary>
	class EventDispatcher
	{
		template <typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		/// <summary>
		/// Constructs an event dispatcher to handle the event that is passed as a parameter
		/// </summary>
		/// <param name="event"></param>
		EventDispatcher(Ref<Event> event)
			: event(std::move(event))
		{
		}

		/// <summary>
		/// Checks if this event matches the template event type and if it does, calls the parameter function passing in the event as a parameter and uses its return to indicate if the event has been handled or not
		/// </summary>
		/// <typeparam name="T">The type of event to look for when dispatching</typeparam>
		/// <param name="func">The function to call to handle the event</param>
		/// <returns>returns a bool indicating if the function was called or not</returns>
		template <typename T>
		bool Dispatch(EventFunc<T> func)
		{
			if (event->GetEventType() == T::GetStaticType())
			{
				event->handled = func(*static_cast<T*>(event.get()));
				return true;
			}
			return false;
		}

	private:
		Ref<Event> event;
	};

	template <typename OStream>
	OStream& operator<<(OStream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
