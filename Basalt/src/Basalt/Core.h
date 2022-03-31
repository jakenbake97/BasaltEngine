#pragma once
#include <memory>

#ifdef BE_PLATFORM_WINDOWS

#else
	#error Basalt currently only supports Windows
#endif

#define BIT(x) (1 << (x))

namespace Basalt
{
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;
}
