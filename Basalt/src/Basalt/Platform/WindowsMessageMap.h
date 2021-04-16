#pragma once

#include <unordered_map>
#include <Windows.h>
#include "../Core.h"

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
