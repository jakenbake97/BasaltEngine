#pragma once
#include <chrono>

namespace Basalt
{
	class Timer
	{
	public:
		/// <summary>
		/// Constructs a timer which starts immediately
		/// </summary>
		Timer();
		/// <summary>
		/// Returns the current time on the timer since it started
		/// </summary>
		/// <returns>The duration of time since the timer was started</returns>
		float GetTime() const;
		/// <summary>
		/// Returns the duration of time between the last frame mark
		/// </summary>
		/// <returns>A duration from the last time Mark was called</returns>
		float GetDeltaTime() const;
		/// <summary>
		/// Marks the beginning of a new frame and sets the delta time as the duration between now and the last delta time
		/// </summary>
		void Mark();
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
		float lastDeltaTime;
	};
}
