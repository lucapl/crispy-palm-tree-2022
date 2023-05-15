#pragma once
#include <chrono>

class Timer {
	private:
		static std::chrono::seconds maxTime;
	public:
		std::chrono::_V2::steady_clock::time_point start;
//		Timer():start(std::chrono::_V2::steady_clock::now()){};
		//static void setStart();
		static Timer* getInstance();
		void setMaxTime(int seconds);
		std::chrono::seconds elapsedTime();
		bool shouldEnd();
};
