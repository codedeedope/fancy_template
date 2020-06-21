#include "Timer.h"

// The Templates
////////////////////////////////////////////////////////////
template<uint32_t N>
static int Timer::internalISR()
{
	//timerAllList[N]->clearInterruptFlag();
	//timerAllList[N]->timerExternalISR();
	return N;
}

#define CODE_AT(NUM) &Timer::internalISR<NUM>
#include "ArrayIndexAtIndexTemplate.h"
#define ARRAY(TYPE, NUMBER, NAME) std::array<TYPE, NUMBER> NAME(ArrayIndexAtIndexTemplate::Numbers<TYPE, NUMBER>::number())

const ARRAY(Timer::ISR_type, 6, Timer::timerInternalISRList);
// equal to
//const std::array<int (* const)(void), 6> Timer::timerInternalISRList({ &Timer::internalISR<0>, &Timer::internalISR<1>, &Timer::internalISR<2>, &Timer::internalISR<3>, &Timer::internalISR<4>, &Timer::internalISR<5> });
////////////////////////////////////////////////////////////

std::array<Timer*, 6> Timer::timerAllList({});

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
