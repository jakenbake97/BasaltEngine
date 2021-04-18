/*
 * Included from the WindowsMessageMap debug class in the Chili Direct3D Engine
 * https://github.com/planetchili/hw3d
 */

#pragma once

#include "WindowsIncludes.h"
#include <unordered_map>
#include "../Basalt/Core.h"

namespace Basalt {
	class String;
}

namespace Basalt::Platform
{

	class BASALT_API WindowsMessageMap
	{
	private:
		std::unordered_map<DWORD, String> map;
	
	public:
		WindowsMessageMap();
		String operator()(DWORD msg, LPARAM lp, WPARAM wp) const;

	};

}
