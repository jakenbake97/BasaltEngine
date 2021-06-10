#pragma once

#ifdef BE_PLATFORM_WINDOWS
	#ifdef BE_BUILD_DLL
		#define BASALT_API __declspec(dllexport)
	#else
		#define BASALT_API __declspec(dllimport)
	#endif
#else
	#error Basalt currently only supports Windows
#endif

#define BIT(x) (1 << (x))
