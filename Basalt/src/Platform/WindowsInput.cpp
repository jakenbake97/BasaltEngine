#include "BEpch.h"
#include "WindowsInput.h"

#include "Basalt/Application.h"
#include "Basalt/Events/KeyboardEvent.h"
#include "Basalt/Events/MouseEvent.h"

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

	void WindowsInput::HandleMouseButtonDown(MouseCode mouseCode)
	{
		mouseButtonStates[mouseCode] = true;
		const auto mouseDown = std::make_shared<MouseButtonPressedEvent>(mouseCode);
		Application::OnEvent(mouseDown);
	}

	void WindowsInput::HandleMouseButtonUp(MouseCode mouseCode)
	{
		mouseButtonStates[mouseCode] = false;
		const auto mouseUp = std::make_shared<MouseButtonReleasedEvent>(mouseCode);
		Application::OnEvent(mouseUp);
	}

	void WindowsInput::HandleMouseMoved(const int x, const int y)
	{
		this->x = x;
		this->y = y;
		const auto mouseMoved = std::make_shared<MouseMovedEvent>(x, y);
		Application::OnEvent(mouseMoved);
	}

	void WindowsInput::HandleMouseWheel(float delta)
	{
		const auto mouseWheel = std::make_shared<MouseScrolledEvent>(delta);
		Application::OnEvent(mouseWheel);
	}

	bool WindowsInput::CheckKey(const KeyCode keycode)
	{
		return keyStates[keycode];
	}

	bool WindowsInput::CheckMouseButton(const MouseCode button)
	{
		return mouseButtonStates[button];
	}

	std::pair<int, int> WindowsInput::CheckMousePosition()
	{
		return { x,y };
	}
}
