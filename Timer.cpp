#include "Timer.h"

template<uint32_t N>
static int Timer::internalISR()
{
	//timerAllList[N]->clearInterruptFlag();
	//timerAllList[N]->timerExternalISR();
	return N;
}

std::array<Timer*, 6> Timer::timerAllList({});
// This shall be automated
const std::array<int (* const)(void), 6> Timer::timerInternalISRList({ &Timer::internalISR<0>, &Timer::internalISR<1>, &Timer::internalISR<2>, &Timer::internalISR<3>, &Timer::internalISR<4>, &Timer::internalISR<5> });

Timer::Timer(uint32_t timerNumber, int (*externalISR)(void))
{
	// Checks
	if (timerNumber > 5) {
		throw;
	}

	if (!externalISR)
	{
		throw;
	}

	//timer objekt gibt es schon mit base bzw. timer number
	if (Timer::timerAllList[timerNumber] != 0) {
		throw;
	}

	// Zuweisungen
	this->timerNumber = timerNumber;
	this->timerExternalISR = externalISR;

	// Übergeben von internalISR
	//::TimerIntRegister(this->timerBase, TIMER_BOTH, Timer::timerInternalISRList[this->timerNumber]);

	// Konsistenzsicherung
	Timer::timerAllList[this->timerNumber] = this;
}

Timer::~Timer()
{
	Timer::timerAllList[this->timerNumber] = reinterpret_cast<Timer*>(0);
}

void Timer::clearInterruptFlag()
{
	return;
}

