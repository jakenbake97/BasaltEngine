#pragma once
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
		virtual ~IInput() {}
	
		static bool GetKey(const int keycode) { return instance->CheckKey(keycode); }
		static bool GetKeyDown(const int keycode) { return instance->CheckKeyDown(keycode); }
		static bool GetKeyUp(const int keycode) { return instance->CheckKeyUp(keycode); }

		static bool GetMouseButton(const int button) { return instance->CheckMouseButton(button); }
		static bool GetMouseButtonDown(const int button) { return instance->CheckMouseButtonDown(button); }
		static bool GetMouseButtonUp(const int button) { return instance->CheckMouseButtonDown(button); }
		static std::pair<float, float> GetMousePosition() { return instance->CheckMousePosition(); }
	
	protected:
		virtual bool CheckKey(int keycode) = 0;
		virtual bool CheckKeyDown(int keycode) = 0;
		virtual bool CheckKeyUp(int keycode) = 0;

		virtual bool CheckMouseButton(int button) = 0;
		virtual bool CheckMouseButtonDown(int button) = 0;
		virtual bool CheckMouseButtonUp(int button) = 0;

		// TODO: Replace with vector2 when implemented
		virtual std::pair<float, float> CheckMousePosition() = 0;

		
	private:
		static IInput* instance;
	};
}
