#pragma once

#include <array>

// This template returns an array of Type T with length n in which at each index a value dependent of a function of this index is stored

/*
Example:
template<uint32_t N>
struct function {
	static uint32_t apply() {
		return N;
	}
};

std::array<size_t, 5> = Numbers<size_t, 5, func>::number();
*/


namespace ArrayIndexAtIndexTemplate {
	template<typename T, size_t i, size_t n, template<size_t> typename Function>
	struct Counter {
		static void down(std::array<T, n>& arr) {
			//arr[i - 1] = CODE_AT(i - 1);
			//arr[i - 1] = func<i - 1>::apply();
			Function<i>::apply();
			Counter<T, i - 1, n, Function>::down(arr);
		}
	};

	template<typename T, size_t n, template<size_t> typename Function>
	struct Counter<T, 0, n, Function> {
		static void down(std::array<T, n>& arr) {
			return;
		}
	};


	//Das ist der geniale Mapper!
	template<template<size_t> typename func, typename Arr, Arr& arr> //fixed: wird in Numbers fixiert
	struct BetterArray {
		template<size_t i> //variable: Wird im Counter aufgerufen
		struct ApplyArray {
			static void apply() {
				arr[i - 1] = func<i - 1>::apply();
			}
		};
	};


	template<typename T, size_t n, template<size_t> typename func>
	struct Numbers {
		static const std::array<T, n> number() {
			static_assert(n >= 1, "n has to at least 1!");
			static_assert(!std::is_const<T>(), "T shall not be const!");
			static std::array<T, n> arr;

			Counter<T, n, n, BetterArray<func, std::array<T, n>, arr>::ApplyArray>::down(arr);
			return arr;
		}
	};
}

