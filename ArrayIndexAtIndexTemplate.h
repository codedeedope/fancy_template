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
	template<typename T, size_t i, size_t n, template<uint32_t> typename func>
	struct Numbers2 {
		static void number(std::array<T, n>& arr) {
			//arr[i - 1] = CODE_AT(i - 1);
			arr[i - 1] = func<i - 1>::apply();
			Numbers2<T, i - 1, n, func>::number(arr);
		}
	};

	template<typename T, size_t n, template<uint32_t> typename func>
	struct Numbers2<T, 0, n, func> {
		static void number(std::array<T, n>& arr) {
			return;
		}
	};

	template<typename T, size_t n, template<uint32_t> typename func>
	struct Numbers {
		static const std::array<T, n> number() {
			static_assert(n >= 1, "n has to at least 1!");
			static_assert(!std::is_const<T>(), "T shall not be const!");
			std::array<T, n> arr;
			Numbers2<T, n, n, func>::number(arr);
			return arr;
		}
	};
}

