#pragma once

#include <array>

// This template returns an array of Type T with length n in which at each index a value dependent of a function of this index is stored

// Abstract use example: std::array<T, size_t> = Numbers<T, size_t>::number();
// Concrete use example: std::array<size_t, 5> = Numbers<size_t, 5>::number();

#ifndef CODE_AT
#error relies on definition of CODE_AT(NUM), which defines what shall be assignet to the array at index num
#endif CODE_AT

namespace ArrayIndexAtIndexTemplate {
	template<typename T, size_t i, size_t n>
	struct Numbers2 {
		static void number(std::array<T, n>& arr) {
			arr[i - 1] = CODE_AT(i - 1);
			Numbers2<T, i - 1, n>::number(arr);
		}
	};

	template<typename T, size_t n>
	struct Numbers2<T, 0, n> {
		static void number(std::array<T, n>& arr) {
			return;
		}
	};

	template<typename T, size_t n>
	struct Numbers {
		static const std::array<T, n> number() {
			static_assert(n >= 1, "n has to at least 1!");
			static_assert(!std::is_const<T>(), "T shall not be const!");
			std::array<T, n> arr;
			Numbers2<T, n, n>::number(arr);
			return arr;
		}
	};
}

