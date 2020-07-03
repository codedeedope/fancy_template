#pragma once

#include <array>


namespace ArrayIndexAtIndexTemplate {
	template<size_t i, template<size_t> typename NumberConsumer>
	struct Counter {
		static void down() {
			NumberConsumer<i>::apply();
			Counter<i - 1, NumberConsumer>::down();
		}
	};


	template<template<size_t> typename NumberConsumer>
	struct Counter<0, NumberConsumer> {
		static void down() {
			NumberConsumer<0>::apply();
			return;
		}
	};


	template<typename ArrayType, ArrayType& arrayRef, template<size_t> typename ExternalNumberConsumer>
	struct GenericArrayAssignment {
		template<size_t i>
		struct NumberConsumer {
			static void apply() {
				if (i == 0) return;
				arrayRef[i - 1] = ExternalNumberConsumer<i - 1>::apply();
			}
		};
	};


	//Array = map({i < arraySize}, i->NumberConsumer(i))
	template<typename ArrayEntryType, size_t arraySize, template<size_t> typename NumberConsumer>
	struct FillArrayIndexDependent {
		typedef std::array<ArrayEntryType, arraySize> ArrayType;

		static ArrayType get() {
			static_assert(arraySize >= 1, "arraySize has to at least 1!");
			static_assert(!std::is_const<ArrayEntryType>(), "ArrayEntryType shall not be const!");

			// In a declaration or a definition of a template, including alias template, a name that is not a member of the current instantiation and is dependent on a template parameter is not considered to be a type unless the keyword typename is used or unless it was already established as a type name, e.g. with a typedef declaration or by being used to name a base class.
			Counter<arraySize, ConcreteArrayAssignment::NumberConsumer>::down();
			return arr;
		}

	private:
		static ArrayType arr;

		typedef GenericArrayAssignment<ArrayType, arr, NumberConsumer> ConcreteArrayAssignment;

		//C++11
		//template<size_t m>
		//using ConcreteArrayAssignmentNumberConsumer = typename ConcreteArrayAssignment::template NumberConsumer<m>;
	};
	template<typename ArrayEntryType, size_t arraySize, template<size_t> typename NumberConsumer>
	typename FillArrayIndexDependent<ArrayEntryType, arraySize, NumberConsumer>::ArrayType FillArrayIndexDependent<ArrayEntryType, arraySize, NumberConsumer>::arr({});
}

