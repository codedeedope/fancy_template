#pragma once

#include <vector>

class Timer
{
public:
	Timer(uint32_t timerNumber, int (*externalISR)(void));
	~Timer();
	void clearInterruptFlag();

private:
	uint32_t timerNumber;
	int (*timerExternalISR)(void);

	static std::vector<Timer*> timerAllList;

	template<uint32_t N>
	static int internalISR()
	{
		//timerAllList[N]->clearInterruptFlag();
		//timerAllList[N]->timerExternalISR();
		return N;
	}

	// tmp for test
public: static std::vector<int (*)(void)> timerInternalISRList;
};

