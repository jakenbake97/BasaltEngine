#include "BEpch.h"
#include "Timer.h"

using namespace std::chrono;

namespace Basalt
{
	Timer::Timer()
	: lastDeltaTime(0)
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
		return lastDeltaTime;
	}

	void Timer::Mark()
	{
		lastDeltaTime = duration<float>(high_resolution_clock::now() - lastTime).count();
		lastTime = high_resolution_clock::now();
	}
}
