#pragma once

#include "Keycodes.h"
#include "Basalt/Core.h"

namespace Basalt
{
	class BASALT_API IInput
	{
	protected:
		IInput() = default;
	public:
		IInput(const IInput& other) = delete;
		IInput& operator=(const IInput& other) = delete;
		IInput(IInput&& other) noexcept = delete;
		IInput& operator=(IInput&& other) noexcept = delete;
		virtual ~IInput() = default;
	
		static bool GetKey(const KeyCode keycode) { return instance->CheckKey(keycode); }

		static bool GetMouseButton(const KeyCode button) { return instance->CheckMouseButton(button); }
		static std::pair<float, float> GetMousePosition() { return instance->CheckMousePosition(); }

		static void OnKeyDown(const KeyCode keycode) { return instance->HandleKeyDown(keycode); }
		static void OnKeyUp(const KeyCode keycode) { return instance->HandleKeyUp(keycode); }
	
	protected:
		virtual bool CheckKey(KeyCode keycode) = 0;
		virtual bool CheckMouseButton(int button) = 0;

		virtual void HandleKeyDown(KeyCode keyCode) = 0;
		virtual void HandleKeyUp(KeyCode keyCode) = 0;
		
		// TODO: Replace with vector2 when implemented
		virtual std::pair<float, float> CheckMousePosition() = 0;
		
	private:
		static IInput* instance;
	};
}
