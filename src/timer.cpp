#include "timer.hpp"

//std::chrono::_V2::steady_clock Timer::start = std::chrono::_V2::steady_clock::now();
std::chrono::seconds Timer::maxTime = std::chrono::seconds{ 1 };
Timer* instance = NULL;
//void Timer::setStart(){
//	Timer::start = std::chrono::_V2::steady_clock::now();
//}
Timer* Timer::getInstance(){
	if(!instance){
		instance = new Timer();
		instance->start = std::chrono::_V2::steady_clock::now();
	}
	return instance;
}
void Timer::setMaxTime(int seconds) {
	maxTime = std::chrono::seconds{ seconds };
}
std::chrono::seconds Timer::elapsedTime() {
	auto now = std::chrono::_V2::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(now - start);
}
bool Timer::shouldEnd() {
	 return elapsedTime() >= maxTime;
}
