#pragma once
#include <chrono>

namespace Basalt
{
	class Timer
	{
	private:
		std::chrono::steady_clock::time_point lastTime;
	public:
		Timer();
		float Mark();
		float Peek() const;
	};
}
