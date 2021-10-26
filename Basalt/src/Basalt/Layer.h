#pragma once
#include <utility>

#include "BEpch.h"

#include "Events/Event.h"

namespace Basalt
{
	class Layer
	{
	public:
		Layer(String name = "Layer") : debugName(std::move(name)) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(std::shared_ptr<Event>& event) {}

		const String& GetName() const { return debugName; }
	protected:
		String debugName;
	};
}
