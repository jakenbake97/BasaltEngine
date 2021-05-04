#pragma once

// Windows
#ifdef BE_PLATFORM_WINDOWS
	// target Windows 7 or later
	#define _WIN32_WINNT 0x0601
	#include <sdkddkver.h>

	#define WIN32_LEAN_AND_MEAN

	// Disable windows' Min and Max to prevent from messing up the std::min and max functions
	#define NOMINMAX

	// Define strict to allow for more portable code and require more care in declaring and using types
	#define STRICT

	#include <Windows.h>
#endif

// Common includes
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Engine includes
#include "Basalt/Core.h"
#include "Basalt/Log.h"
#include "Basalt/Utility/String.h"