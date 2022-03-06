#pragma once
#include <utility>

#include "BEpch.h"

#include "Events/Event.h"

namespace Basalt
{
	/// <summary>
	/// A generic layer that can be added to the layer stack to get a regular update call
	/// </summary>
	class Layer
	{
	public:
		/// <summary>
		/// Constructs a layer with the given name
		/// </summary>
		/// <param name="name">[Optional] The name of the layer</param>
		Layer(String name = "Layer") : debugName(std::move(name)) {}
		virtual ~Layer() = default;

		/// <summary>
		/// Event used to initialize the layer when it is pushed onto the layer stack
		/// </summary>
		virtual void OnAttach() {}
		/// <summary>
		/// Event used to shutdown the layer when it is popped from the layer stack
		/// </summary>
		virtual void OnDetach() {}
		/// <summary>
		/// Event used to update the layer each frame of the application
		/// </summary>
		/// <param name="deltaTime">The time the last frame took to complete</param>
		virtual void OnUpdate(float deltaTime) {}
		/// <summary>
		/// Event used for rendering any ImGUI draw calls, called after the update loop.
		/// </summary>
		virtual void OnImGuiRender() {}
		/// <summary>
		/// Event used to pass other events to this layer to be dispatched
		/// </summary>
		/// <param name="event"></param>
		virtual void OnEvent(std::shared_ptr<Event>& event) {}

		/// <summary>
		/// Returns the name of the layer
		/// </summary>
		/// <returns>The name of the layer</returns>
		const String& GetName() const { return debugName; }
	protected:
		String debugName;
	};
}
