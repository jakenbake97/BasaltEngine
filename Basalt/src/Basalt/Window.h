#pragma once
#include "BEpch.h"

#include "Input.h"
#include "Renderer/RenderContext.h"

namespace Basalt
{
	struct WindowProperties
	{
		String title;
		unsigned int width;
		unsigned int height;

		WindowProperties(String title = "Basalt Engine", const unsigned int width = 1280, const unsigned int height = 720)
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
		
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetWindowHandle() = 0;

		static std::unique_ptr<Window> Create(const WindowProperties& properties = WindowProperties());

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
