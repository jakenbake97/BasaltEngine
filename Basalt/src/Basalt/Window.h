#pragma once
#include "BEpch.h"

#include "Input.h"

namespace Basalt
{
	struct WindowProperties
	{
		String title;
		uint32 width;
		uint32 height;

		WindowProperties(String title = "Basalt Engine", const uint32 width = 1280, const uint32 height = 720)
			: title(std::move(title)), width(width), height(height)
		{}
	};

	class Window
	{
	protected:
		Window() = default;
	public:
		Window(const Window& other) = delete;
		Window(Window&& other) noexcept = delete;
		Window& operator=(const Window& other) = delete;
		Window& operator=(Window&& other) noexcept = delete;

		static std::unique_ptr<Window> Create(const WindowProperties& properties = WindowProperties());

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		// Window attributes
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetWindowHandle() const = 0;

	protected:
		static void ClearInputState() { Input::ClearState(); }
		static void OnKeyDown(const KeyCode keyCode) { Input::OnKeyDown(keyCode); }
		static void OnKeyUp(const KeyCode keyCode) { Input::OnKeyUp(keyCode); }
		static void OnMouseButtonDown(const MouseCode mouseCode) { Input::OnMouseButtonDown(mouseCode); }
		static void OnMouseButtonUp(const MouseCode mouseCode) { Input::OnMouseButtonUp(mouseCode); }
		static void OnMouseMoved(const int xPos, const int yPos) { Input::OnMouseMoved(xPos, yPos); }
		static void OnMouseWheel(const int wheelDelta) { Input::OnMouseWheel(wheelDelta); }
		static void OnMouseEnter() { Input::OnMouseEnter(); }
		static void OnMouseLeave() { Input::OnMouseLeave(); }
	};
}
