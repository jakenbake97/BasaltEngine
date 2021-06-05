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

		bool CheckMouseButton(int button) override;
		std::pair<float, float> CheckMousePosition() override;
	private:
		void HandleKeyDown(KeyCode keycode) override;
		void HandleKeyUp(KeyCode keycode) override;
		void ClearInputStates() override;

		bool autoRepeatEnabled = false;
		std::unordered_map<KeyCode, bool> keyStates;
	};
}
