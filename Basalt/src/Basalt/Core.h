#pragma once

#ifdef BAS_PLATFORM_WINDOWS
	#ifdef BAS_BUILD_DLL
		#define BASALT_API __declspec(dllexport)
	#else
		#define BASALT_API __declspec(dllimport)
	#endif
#else
	#error Basalt currently only supports Windows
#endif
