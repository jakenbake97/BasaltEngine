#include "BEpch.h"
#include "Timer.h"

using namespace std::chrono;

namespace Basalt
{
	Timer::Timer()
	{
		startTime = high_resolution_clock::now();
		lastTime = high_resolution_clock::now();
	}

	float Timer::GetTime() const
	{
		return duration<float>(high_resolution_clock::now() - startTime).count();
	}

	float Timer::GetDeltaTime() const
	{
		return duration<float>(high_resolution_clock::now() - lastTime).count();
	}

	void Timer::Mark()
	{
		lastTime = high_resolution_clock::now();
	}
}
