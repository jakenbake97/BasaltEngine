#pragma once
#include "BEpch.h"

#include "IInput.h"
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

	class IWindow
	{
	protected:
		IWindow() = default;
	public:
		IWindow(const IWindow& other) = delete;
		IWindow(IWindow&& other) noexcept = delete;
		IWindow& operator=(const IWindow& other) = delete;
		IWindow& operator=(IWindow&& other) noexcept = delete;
		
		virtual ~IWindow() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetWindowHandle() = 0;

		static std::unique_ptr<IWindow> Create(const WindowProperties& properties = WindowProperties());

	protected:
		static void ClearInputState() { IInput::ClearState(); }
		static void OnKeyDown(const KeyCode keyCode) { IInput::OnKeyDown(keyCode); }
		static void OnKeyUp(const KeyCode keyCode) { IInput::OnKeyUp(keyCode); }
		static void OnMouseButtonDown(const MouseCode mouseCode) { IInput::OnMouseButtonDown(mouseCode); }
		static void OnMouseButtonUp(const MouseCode mouseCode) { IInput::OnMouseButtonUp(mouseCode); }
		static void OnMouseMoved(const int xPos, const int yPos) { IInput::OnMouseMoved(xPos, yPos); }
		static void OnMouseWheel(const int wheelDelta) { IInput::OnMouseWheel(wheelDelta); }
		static void OnMouseEnter() { IInput::OnMouseEnter(); }
		static void OnMouseLeave() { IInput::OnMouseLeave(); }
	};
}
