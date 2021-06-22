#pragma once

#ifdef BE_PLATFORM_WINDOWS

#else
	#error Basalt currently only supports Windows
#endif

#define BIT(x) (1 << (x))
