#include "../../include/Time/Time.hpp"

namespace engine {

	Time::Time()
		: startTime()
		, endTime()
		, freqTime()
	{
		// ���x�̎擾
		if (QueryPerformanceFrequency(&freqTime) == FALSE) {
			return;
		}

		// �ŏ��ɌĂ΂ꂽ��
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