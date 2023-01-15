#include "timer.hpp"

std::chrono::steady_clock::time_point Timer::start = std::chrono::high_resolution_clock::now();
std::chrono::seconds Timer::maxTime = std::chrono::seconds{ 1 };

void Timer::setMaxTime(int seconds) {
	maxTime = std::chrono::seconds{ seconds };
}
std::chrono::seconds Timer::elapsedTime() {
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(now - start);
}
bool Timer::shouldEnd() {
	 return elapsedTime() >= maxTime;
}