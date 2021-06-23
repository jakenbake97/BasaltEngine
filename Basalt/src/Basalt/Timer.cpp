#include "BEpch.h"
#include "Timer.h"

using namespace std::chrono;

namespace Basalt
{
	Timer::Timer()
	{
		lastTime = steady_clock::now();
	}

	float Timer::Mark()
	{
		const auto old = lastTime;
		lastTime = steady_clock::now();
		const duration<float> frameTime = lastTime - old;
		return frameTime.count();
	}

	float Timer::Peek() const
	{
		return duration<float>(steady_clock::now() - lastTime).count();
	}
}
