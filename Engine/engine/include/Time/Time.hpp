#pragma once

#include <Windows.h>

namespace engine {
	class Time {
	public:
		Time();
		~Time();

		void updateStartTime();

		void updateEndTime();

		LONGLONG getTime();

		LONGLONG getStartTime();

		LONGLONG getEndTIme();

		LONGLONG deltaTime();

		LONGLONG getFreq();

	private:
		LARGE_INTEGER startTime;
		LARGE_INTEGER endTime;
		LARGE_INTEGER freqTime;  // é¸îgêî
	};

}