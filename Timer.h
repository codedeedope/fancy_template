#pragma once

#include <array>

class Timer
{
public:
	typedef size_t(*ISR_type)(void);

	Timer(size_t timerNumber, Timer::ISR_type externalISR);
	~Timer();
	void clearInterruptFlag();

private:
	static const size_t timerAllCount = 6;
	size_t timerNumber;
	Timer::ISR_type timerExternalISR;

	static std::array<Timer*, Timer::timerAllCount> timerAllList;

	// tmp for test
public: static const std::array<ISR_type, Timer::timerAllCount> timerInternalISRList;
};

