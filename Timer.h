#pragma once

#include <array>

class Timer
{
public:
	Timer(uint32_t timerNumber, int (*externalISR)(void));
	~Timer();
	void clearInterruptFlag();

	typedef int (*ISR_type)(void);

private:
	uint32_t timerNumber;
	int (*timerExternalISR)(void);

	static std::array<Timer*, 6> timerAllList;

	// tmp for test
public: static const std::array<ISR_type, 6> timerInternalISRList;
};
