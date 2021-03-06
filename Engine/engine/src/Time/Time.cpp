#include "../../include/Time/Time.hpp"

namespace engine {

	Time::Time()
		: startTime()
		, endTime()
		, freqTime()
	{
		// 精度の取得
		if (QueryPerformanceFrequency(&freqTime) == FALSE) {
			return;
		}

		// 最初に呼ばれた時
		QueryPerformanceCounter(&endTime);
	}


	Time::~Time()
	{
	}

	void Time::updateStartTime()
	{
		QueryPerformanceCounter(&startTime);
	}

	void Time::updateEndTime()
	{
		endTime = startTime;
	}

	LONGLONG Time::getTime()
	{
		LARGE_INTEGER nowTime{};
		QueryPerformanceCounter(&nowTime);
		return nowTime.QuadPart;
	}

	LONGLONG Time::getStartTime()
	{
		return startTime.QuadPart;
	}

	LONGLONG Time::getEndTIme()
	{
		return endTime.QuadPart;
	}

	LONGLONG Time::deltaTime()
	{
		return startTime.QuadPart - endTime.QuadPart;
	}

	LONGLONG Time::getFreq()
	{
		return freqTime.QuadPart;
	}
}