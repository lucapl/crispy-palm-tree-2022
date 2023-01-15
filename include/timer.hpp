#pragma once
#include <chrono>

class Timer {
	private:
		static std::chrono::steady_clock::time_point start;
		static std::chrono::seconds maxTime;
	public:
		static void setMaxTime(int seconds);
		static std::chrono::seconds elapsedTime();
		static bool shouldEnd();
};