#pragma once
#include "Basalt/Layer.h"

namespace Basalt
{
	/// <summary>
	/// A type of layer for ImGUI related rendering and commands
	/// </summary>
	class ImGuiLayer : public Layer
	{
	public:
		/// <summary>
		/// Constructs an ImGUI layer to be added to the application layer stack
		/// </summary>
		ImGuiLayer();
		~ImGuiLayer() override = default;

		/// <summary>
		/// Event used to initialize ImGUI when the layer is pushed onto the layer stack
		/// </summary>
		void OnAttach() override;

		/// <summary>
		/// Event used to shutdown ImGUI when the layer is popped from the layer stack
		/// </summary>
		void OnDetach() override;

		/// <summary>
		/// Event used for rendering any ImGUI draw calls, called after the update loop.
		/// </summary>
		void OnImGuiRender() override;

		/// <summary>
		/// Marks the beginning of an ImGUI frame
		/// </summary>
		void Begin();

		/// <summary>
		/// Marks the end of an ImGUI frame, indicating it is ok to swap buffers
		/// </summary>
		void End();
	};
}
