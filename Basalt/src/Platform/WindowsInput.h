#pragma once

#include "Basalt/Core.h"
#include "Basalt/IInput.h"
#include "Basalt/Keycodes.h"

namespace Basalt::Platform
{
	class BASALT_API WindowsInput : public IInput
	{
	protected:
		bool CheckKey(KeyCode keycode) override;

		bool CheckMouseButton(MouseCode button) override;
		std::pair<int, int> CheckMousePosition() override;
	private:
		void HandleKeyDown(KeyCode keycode) override;
		void HandleKeyUp(KeyCode keycode) override;
		void ClearInputStates() override;

		void HandleMouseButtonDown(MouseCode mouseCode) override;
		void HandleMouseButtonUp(MouseCode mouseCode) override;
		void HandleMouseMoved(int x, int y) override;
		void HandleMouseWheel(float delta) override;

		std::unordered_map<KeyCode, bool> keyStates;
		std::unordered_map<MouseCode, bool> mouseButtonStates;
		int x = 0;
		int y = 0;
	};
}
