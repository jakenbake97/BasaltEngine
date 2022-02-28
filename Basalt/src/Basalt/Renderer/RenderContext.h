#pragma once

namespace Basalt
{
	class Window;

	/// <summary>
	/// An interface to the api specific derived implementations of this class
	/// </summary>
	class RenderContext
	{
	protected:
		RenderContext() = default;
	public:
		RenderContext(const RenderContext& other) = delete;
		RenderContext(RenderContext&& other) noexcept = delete;
		RenderContext& operator=(const RenderContext& other) = delete;
		RenderContext& operator=(RenderContext&& other) noexcept = delete;
		virtual ~RenderContext() = default;
		
		/// <summary>
		/// Interface to the render api specific function to swap frame buffers
		/// </summary>
		/// <param name="isVsync">indicates if vsync is enabled or not</param>
		virtual void SwapBuffers(bool isVsync) = 0;

		/// <summary>
		/// Interface to the render api specific function that clears the frame
		/// </summary>
		/// <param name="color">the color to clear the frame to</param>
		virtual void ClearColor(Color color) = 0;

		/// <summary>
		/// Returns a pointer to the render api specific device (physical device)
		/// </summary>
		/// <returns>a void pointer to the device</returns>
		virtual void* GetDevice() = 0;

		/// <summary>
		/// Returns a pointer to the render api specific device context (logical device)
		/// </summary>
		/// <returns>a void pointer to the device context</returns>
		virtual void* GetDeviceContext() = 0;

		/// <summary>
		/// Creates a render context for the selected render api and returns a pointer to this interface
		/// </summary>
		/// <param name="window">a const reference to the window which will be rendered to, this is used to get the window handle</param>
		/// <returns>a unique pointer to the RenderContext base class</returns>
		static std::unique_ptr<RenderContext> CreateRenderContext(const Window& window);
	};
}
