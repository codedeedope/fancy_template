#pragma once

#include <array>

namespace ArrayIndexAtIndexTemplate {
	template<typename T, size_t i, size_t n> struct Numbers2;
}

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
	template<typename T, size_t i, size_t n> friend struct ArrayIndexAtIndexTemplate::Numbers2;
	typedef int (*ISR_type)(void);

	// tmp for test
public: static const std::array<ISR_type, 6> timerInternalISRList;
};
