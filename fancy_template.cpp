// fancy_template.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Timer.h"

#define PTR(NUM) int (*p##NUM)(void) = Timer::timerInternalISRList[NUM];
#define EX(NUM) int i##NUM = p##NUM();
#define PTREX(NUM) PTR(NUM) EX(NUM)

#include <array>

template<size_t i, size_t n>
struct Numbers2 {
	static void number(std::array<size_t, n>& arr) {
		arr[i - 1] = i-1;
		Numbers2<i - 1, n>::number(arr);
	}
};

template<size_t n>
struct Numbers2<0, n> {
	static void number(std::array<size_t, n>& arr) {
		return;
	}
};

template<size_t n>
struct Numbers {
	static std::array<size_t, n> number() {
		static_assert(n >= 1);
		std::array<size_t, n> arr;
		arr[n - 1] = n-1;
		Numbers2<n-1, n>::number(arr);
		return arr;
	}
};

static const std::array<size_t, 3> theArr(Numbers<3>::number());


int main()
{
	size_t a = theArr[2];

	std::cout << "Hello World!\n";

	size_t pt = Timer::timerInternalISRList.size();

	PTREX(0)
		PTREX(1)
		PTREX(2)
		PTREX(3)
		PTREX(4)
		PTREX(5)

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
