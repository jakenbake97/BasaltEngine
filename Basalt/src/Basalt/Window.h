#pragma once
#include "BEpch.h"

#include "Input.h"

namespace Basalt
{
	struct WindowProperties
	{
		String title;
		uint16 width;
		uint16 height;

		/// <summary>
		/// Creates properties for the window to use when it is created
		/// </summary>
		/// <param name="title">[Optional] The title to display on the window</param>
		/// <param name="width">[Optional] The width in pixels of the window</param>
		/// <param name="height">[Optional] The height in pixels of the window</param>
		WindowProperties(String title = "Basalt Engine", const uint16 width = 1280, const uint16 height = 720)
			: title(std::move(title)), width(width), height(height)
		{}
	};

	/// <summary>
	/// An operating system agnostic interface to the window
	/// </summary>
	class Window
	{
	protected:
		Window() = default;
	public:
		Window(const Window& other) = delete;
		Window(Window&& other) noexcept = delete;
		Window& operator=(const Window& other) = delete;
		Window& operator=(Window&& other) noexcept = delete;

		/// <summary>
		/// Creates a window based on the current operating system
		/// </summary>
		/// <param name="properties">The properties to use to create the window</param>
		/// <returns>A unique pointer to the window that was created</returns>
		static Scope<Window> Create(const WindowProperties& properties = WindowProperties());

		virtual ~Window() = default;

		/// <summary>
		/// Runs the window's message loop to process inputs and events.
		/// </summary>
		virtual void OnUpdate() = 0;

		// Window attributes
		/// <summary>
		/// Returns the width of the window
		/// </summary>
		/// <returns>The width of the window in pixels</returns>
		virtual uint32 GetWidth() const = 0;
		/// <summary>
		/// Returns the height of the window
		/// </summary>
		/// <returns>The height of the window in pixels</returns>
		virtual uint32 GetHeight() const = 0;

		/// <summary>
		/// Sets the window to either enable or disable Vsync when rendering
		/// </summary>
		/// <param name="enabled">Indicates whether the window should update immediately or wait until a vblank</param>
		virtual void SetVSync(bool enabled) = 0;
		/// <summary>
		/// Returns a bool indicating if Vsync is enabled for this window
		/// </summary>
		/// <returns>True if vsync is enabled, false if vsync is disabled</returns>
		virtual bool IsVSync() const = 0;

		/// <summary>
		/// Returns the pointer to the window handle
		/// </summary>
		/// <returns>a void pointer to the window which can be cast to the specific operating system window</returns>
		virtual void* GetWindowHandle() const = 0;

	protected:
		static void ClearInputState() { Input::ClearState(); }
		static void OnKeyDown(const KeyCode keyCode) { Input::OnKeyDown(keyCode); }
		static void OnKeyUp(const KeyCode keyCode) { Input::OnKeyUp(keyCode); }
		static void OnMouseButtonDown(const MouseCode mouseCode) { Input::OnMouseButtonDown(mouseCode); }
		static void OnMouseButtonUp(const MouseCode mouseCode) { Input::OnMouseButtonUp(mouseCode); }
		static void OnMouseMoved(const Vector2Int position) { Input::OnMouseMoved(position); }
		static void OnMouseWheel(const int wheelDelta) { Input::OnMouseWheel(wheelDelta); }
		static void OnMouseEnter() { Input::OnMouseEnter(); }
		static void OnMouseLeave() { Input::OnMouseLeave(); }
	};
}
