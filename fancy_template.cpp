// fancy_template.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Timer.h"

#define PTR(NUM) int (*p##NUM)(void) = Timer::timerInternalISRList[NUM];
#define EX(NUM) int i##NUM = p##NUM();
#define PTREX(NUM) PTR(NUM) EX(NUM)

int main()
{
	std::cout << "Hello World!\n";

	size_t pt = Timer::timerInternalISRList.size();

	PTREX(0)
		PTREX(1)
		PTREX(2)
		PTREX(3)
		PTREX(4)
		PTREX(5)

}
