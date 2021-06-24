﻿#pragma once
#include <chrono>

namespace Basalt
{
	class Timer
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
	public:
		Timer();
		float GetTime() const;
		float GetDeltaTime() const;
		void Mark();
	};
}