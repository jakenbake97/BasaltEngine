#pragma once

#include "Basalt/Core.h"
#include "Basalt/Input.h"
#include "Basalt/Keycodes.h"

namespace Basalt::Platform
{
	class BASALT_API WindowsInput : public IInput
	{
		friend class Window;

		class KeyAction
		{
		public:
			enum class Type
			{
				KeyDown,
				KeyUp,
				KeyRepeat,
				Invalid
			};
		private:
			Type type;
			int keycode;

		public:
			KeyAction()
				: type(Type::Invalid), keycode(-1) {}
			KeyAction(const Type type, const int keycode)
				: type(type), keycode(keycode) {}
			bool IsKeyDown() const
			{
				return type == Type::KeyDown;
			}
			bool IsKeyUp() const
			{
				return type == Type::KeyUp;
			}
			bool IsValid() const
			{
				return type != Type::Invalid;
			}
			int GetKeycode() const
			{
				return keycode;
			}
		};
		
	public:
		KeyAction ReadKey();
		void ClearKey();
		void EnableAutoRepeat();
		void DisableAutoRepeat();
		bool IsAutoRepeatEnabled() const;
	protected:
		bool CheckKey(int keycode) override;
		bool CheckKeyDown(int keycode) override;
		bool CheckKeyUp(int keycode) override;

		bool CheckMouseButton(int button) override;
		bool CheckMouseButtonDown(int button) override;
		bool CheckMouseButtonUp(int button) override;
		std::pair<float, float> CheckMousePosition() override;
	private:
		void OnKeyDown(unsigned char keycode);
		void OnKeyUp(unsigned char keycode);
		void ClearState();

		void TrimBuffer();

		static constexpr unsigned int bufferSize = 16u;
		bool autoRepeatEnabled = false;
		std::unordered_map<int, bool> keyStates;
		std::queue<KeyAction> keyBuffer;
	};
}
