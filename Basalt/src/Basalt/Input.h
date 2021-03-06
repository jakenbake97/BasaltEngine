#pragma once

#include "Keycodes.h"
#include "MouseCodes.h"
#include "Basalt/Core.h"

namespace Basalt
{
	class Input
	{
		friend class Window;
	protected:
		Input() = default;
	public:
		Input(const Input& other) = delete;
		Input& operator=(const Input& other) = delete;
		Input(Input&& other) noexcept = delete;
		Input& operator=(Input&& other) noexcept = delete;
		virtual ~Input() = default;

		/// <summary>
		/// Returns a bool indicating if the key <paramref name="keycode"/> is pressed or not
		/// </summary>
		/// <param name="keycode">The key to check the status of</param>
		/// <returns>True if the key is pressed. False if it is not</returns>
		static bool GetKey(const KeyCode keycode) { return instance->CheckKey(keycode); }

		/// <summary>
		/// Returns a bool indicating if the mouse <paramref name="button"/> is pressed or not
		/// </summary>
		/// <param name="button">The button to check the status of</param>
		/// <returns>True if they button is pressed. False if it is not</returns>
		static bool GetMouseButton(const KeyCode button) { return instance->CheckMouseButton(button); }
		/// <summary>
		/// Returns the current position of the mouse on the window
		/// </summary>
		/// <returns>The position of the mouse relative to the window</returns>
		static Vector2Int GetMousePosition() { return instance->CheckMousePosition(); }
		/// <summary>
		/// Returns a bool indicating if the mouse cursor is inside or outside of the window
		/// </summary>
		/// <returns>True if the mouse is inside the window. False if the mouse is outside of the window</returns>
		static bool IsMouseInWindow() { return instance->CheckMouseInWindow(); }

	protected:
		static void OnKeyDown(const KeyCode keycode) { return instance->HandleKeyDown(keycode); }
		static void OnKeyUp(const KeyCode keycode) { return instance->HandleKeyUp(keycode); }

		static void OnMouseButtonDown(const MouseCode mouseCode) { return instance->HandleMouseButtonDown(mouseCode); }
		static void OnMouseButtonUp(const MouseCode mouseCode) { return instance->HandleMouseButtonUp(mouseCode); }
		static void OnMouseMoved(const Vector2Int position) { return instance->HandleMouseMoved(position); }
		static void OnMouseWheel(const int wheelDelta) { return instance->HandleMouseWheel(wheelDelta); }

		static void OnMouseEnter() { return instance->HandleMouseEnter(); }
		static void OnMouseLeave() { return instance->HandleMouseLeave(); }

		static void ClearState() { return instance->ClearInputStates(); }
		
		virtual bool CheckKey(KeyCode keycode) = 0;
		virtual bool CheckMouseButton(MouseCode button) = 0;
		virtual Vector2Int CheckMousePosition() = 0;
		virtual bool CheckMouseInWindow() = 0;

		virtual void HandleKeyDown(KeyCode keyCode) = 0;
		virtual void HandleKeyUp(KeyCode keyCode) = 0;
		
		virtual void HandleMouseButtonDown(MouseCode mouseCode) = 0;
		virtual void HandleMouseButtonUp(MouseCode mouseCode) = 0;
		virtual void HandleMouseMoved(Vector2Int position) = 0;
		virtual void HandleMouseWheel(int delta) = 0;

		virtual void HandleMouseEnter() = 0;
		virtual void HandleMouseLeave() = 0;

		virtual void ClearInputStates() = 0;
		
	private:
		static Scope<Input> instance;
	};
}
