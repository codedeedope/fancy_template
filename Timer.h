#pragma once

#include <array>

class Timer
{
public:
	Timer(uint32_t timerNumber, int (*externalISR)(void));
	~Timer();
	void clearInterruptFlag();

private:
	uint32_t timerNumber;
	int (*timerExternalISR)(void);

	static std::array<Timer*, 6> timerAllList;

	template<uint32_t N> static int internalISR();

	// tmp for test
public: static const std::array<int (* const)(void), 6> timerInternalISRList;
};
