#pragma once
#include "Layer.h"

namespace Basalt
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		/// <summary>
		/// Pushes a layer onto the layer stack to be included in events and updated
		/// </summary>
		/// <param name="layer">The layer to add to the stack</param>
		void PushLayer(const Ref<Layer>& layer);
		/// <summary>
		/// Pushes an overlay layer onto the layer stack to be included in events and updated. Overlays are after all normal layers
		/// </summary>
		/// <param name="overlay">The overlay layer to add to the stack</param>
		void PushOverlay(const Ref<Layer>& overlay);
		/// <summary>
		/// Removes the layer <paramref name="layer"/> from the stack
		/// </summary>
		/// <param name="layer">The layer to remove from the stack</param>
		void PopLayer(const Ref<Layer>& layer);
		/// <summary>
		/// Removes the overlay layer <paramref name="overlay"/> from the stack
		/// </summary>
		/// <param name="overlay">The overlay layer to remove from the stack</param>
		void PopOverlay(const Ref<Layer>& overlay);

		std::vector<Ref<Layer>>::iterator begin() { return layers.begin(); }
		std::vector<Ref<Layer>>::iterator end() { return layers.end(); }
		std::vector<Ref<Layer>>::reverse_iterator rbegin() { return layers.rbegin(); }
		std::vector<Ref<Layer>>::reverse_iterator rend() { return layers.rend(); }

		std::vector<Ref<Layer>>::const_iterator begin() const { return layers.begin(); }
		std::vector<Ref<Layer>>::const_iterator end() const { return layers.end(); }
		std::vector<Ref<Layer>>::const_reverse_iterator rbegin() const { return layers.rbegin(); }
		std::vector<Ref<Layer>>::const_reverse_iterator rend() const { return layers.rend(); }

	private:
		std::vector<Ref<Layer>> layers;
		unsigned int layerInsertionIndex = 0;
	};
}
