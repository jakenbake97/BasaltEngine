#include "BEpch.h"
#include "LayerStack.h"

Basalt::LayerStack::~LayerStack()
{
	for (const auto& layer : layers)
	{
		layer->OnDetach();
	}
}

void Basalt::LayerStack::PushLayer(const Ref<Layer>& layer)
{
	layers.emplace(layers.begin() + layerInsertionIndex, layer);
	layerInsertionIndex++;
}

void Basalt::LayerStack::PushOverlay(const Ref<Layer>& overlay)
{
	layers.emplace_back(overlay);
}

void Basalt::LayerStack::PopLayer(const Ref<Layer>& layer)
{
	const auto iterator = std::find(layers.begin(), layers.begin() + layerInsertionIndex, layer);
	if (iterator != layers.begin() + layerInsertionIndex)
	{
		layer->OnDetach();
		layers.erase(iterator);
		layerInsertionIndex--;
	}
}

void Basalt::LayerStack::PopOverlay(const Ref<Layer>& overlay)
{
	const auto iterator = std::find(layers.begin() + layerInsertionIndex, layers.end(), overlay);
	if (iterator != layers.end())
	{
		overlay->OnDetach();
		layers.erase(iterator);
	}
}
