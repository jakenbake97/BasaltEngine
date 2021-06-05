#include "BEpch.h"
#include "WindowsInput.h"

#include "Basalt/Application.h"
#include "Basalt/Events/KeyboardEvent.h"

namespace Basalt
{
	IInput* IInput::instance = new Platform::WindowsInput();
}

namespace Basalt::Platform
{

	void WindowsInput::HandleKeyDown(const KeyCode keycode)
	{
		keyStates[keycode] = true;
		const auto keyDown = std::make_shared<KeyPressedEvent>(keycode, 0);
		Application::OnEvent(keyDown);
	}

	void WindowsInput::HandleKeyUp(const KeyCode keycode)
	{
		keyStates[keycode] = false;
		const auto keyUp = std::make_shared<KeyReleasedEvent>(keycode);
		Application::OnEvent(keyUp);
	}

	void WindowsInput::ClearInputStates()
	{
		keyStates.clear();
	}

	bool WindowsInput::CheckKey(const KeyCode keycode)
	{
		return keyStates[keycode];
	}

	bool WindowsInput::CheckMouseButton(int button)
	{
		return false;
	}

	std::pair<float, float> WindowsInput::CheckMousePosition()
	{
		return { 0,0 };
	}
}
