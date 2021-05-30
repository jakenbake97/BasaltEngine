#pragma once

#include "Basalt/Core.h"
#include "Basalt/IInput.h"
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
			KeyCode keycode;

		public:
			KeyAction()
				: type(Type::Invalid), keycode(-1) {}
			KeyAction(const Type type, const KeyCode keycode)
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
			KeyCode GetKeycode() const
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
		bool CheckKey(KeyCode keycode) override;

		bool CheckMouseButton(int button) override;
		std::pair<float, float> CheckMousePosition() override;
	private:
		void HandleKeyDown(KeyCode keycode) override;
		void HandleKeyUp(KeyCode keycode) override;
		void ClearState();

		void TrimBuffer();

		static constexpr unsigned int bufferSize = 16u;
		bool autoRepeatEnabled = false;
		std::unordered_map<KeyCode, bool> keyStates;
		std::queue<KeyAction> keyBuffer;
	};
}
