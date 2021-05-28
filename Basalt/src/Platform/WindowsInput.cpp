#include "BEpch.h"
#include "WindowsInput.h"

namespace Basalt
{
	IInput* IInput::instance = new Platform::WindowsInput();
}

namespace Basalt::Platform
{
	WindowsInput::KeyAction WindowsInput::ReadKey()
	{
		if (keyBuffer.empty())
		{
			return KeyAction();
		}
		const KeyAction key = keyBuffer.front();
		keyBuffer.pop();
		return key;
	}

	void WindowsInput::ClearKey()
	{
		keyBuffer = std::queue<KeyAction>();
	}

	void WindowsInput::EnableAutoRepeat()
	{
		autoRepeatEnabled = true;
	}

	void WindowsInput::DisableAutoRepeat()
	{
		autoRepeatEnabled = false;
	}

	bool WindowsInput::IsAutoRepeatEnabled() const
	{
		return autoRepeatEnabled;
	}

	void WindowsInput::OnKeyDown(const unsigned char keycode)
	{
		const KeyCode basaltCode = Key::ConvertToBasaltKeyCode.at(keycode);
		keyStates[basaltCode] = true;
	}

	void WindowsInput::OnKeyUp(const unsigned char keycode)
	{
		const KeyCode basaltCode = Key::ConvertToBasaltKeyCode.at(keycode);
		keyStates[basaltCode] = false;
	}

	void WindowsInput::ClearState()
	{
		keyStates.clear();
	}

	void WindowsInput::TrimBuffer()
	{
		while(keyBuffer.size() > bufferSize)
		{
			keyBuffer.pop();
		}
	}

	bool WindowsInput::CheckKey(const int keycode)
	{
		return keyStates[keycode];
	}

	bool WindowsInput::CheckKeyDown(int keycode)
	{
		return false;
	}

	bool WindowsInput::CheckKeyUp(int keycode)
	{
		return false;
	}

	bool WindowsInput::CheckMouseButton(int button)
	{
		return false;
	}

	bool WindowsInput::CheckMouseButtonDown(int button)
	{
		return false;
	}

	bool WindowsInput::CheckMouseButtonUp(int button)
	{
		return false;
	}

	std::pair<float, float> WindowsInput::CheckMousePosition()
	{
		return { 0,0 };
	}
}
