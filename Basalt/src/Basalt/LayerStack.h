#pragma once
#include "Layer.h"

namespace Basalt
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(const std::shared_ptr<Layer>& layer);
		void PushOverlay(const std::shared_ptr<Layer>& overlay);
		void PopLayer(const std::shared_ptr<Layer>& layer);
		void PopOverlay(const std::shared_ptr<Layer>& overlay);

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return layers.end(); }
		std::vector<std::shared_ptr<Layer>>::reverse_iterator rbegin() { return layers.rbegin(); }
		std::vector<std::shared_ptr<Layer>>::reverse_iterator rend() { return layers.rend(); }

		std::vector<std::shared_ptr<Layer>>::const_iterator begin() const { return layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::const_iterator end() const { return layers.end(); }
		std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rbegin() const { return layers.rbegin(); }
		std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rend() const { return layers.rend(); }

	private:
		std::vector<std::shared_ptr<Layer>> layers;
		unsigned int layerInsertionIndex = 0;
	};
}
