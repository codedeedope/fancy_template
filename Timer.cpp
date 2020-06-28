#include "Timer.h"

// The Templates
////////////////////////////////////////////////////////////
#include "ArrayIndexAtIndexTemplate.h"

template<size_t N>
static size_t internalISR()
{
	//timerAllList[N]->clearInterruptFlag();
	//timerAllList[N]->timerExternalISR();
	return N;
}


template<size_t N>
struct getPointerToInternalISR {
	static Timer::ISR_type apply() {
		return &internalISR<N>;
	}
};


const std::array<Timer::ISR_type, Timer::timerAllCount> Timer::timerInternalISRList(ArrayIndexAtIndexTemplate::FillArrayIndexDependent<ISR_type, Timer::timerAllCount, getPointerToInternalISR>::get());
// equal to
//const std::array<Timer::ISR_type, 6> Timer::timerInternalISRList({ &Timer::internalISR<0>, &Timer::internalISR<1>, &Timer::internalISR<2>, &Timer::internalISR<3>, &Timer::internalISR<4>, &Timer::internalISR<5> });
////////////////////////////////////////////////////////////

std::array<Timer*, Timer::timerAllCount> Timer::timerAllList({});


Timer::Timer(size_t timerNumber, ISR_type externalISR)
{
	// Checks
	if (timerNumber > (Timer::timerAllCount - 1)) {
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

