#include <iostream>

#include "literals.h"
#include "types.h"
#include "automatic_type_deduction.h"
#include "casts.h"
#include "unified_initialization.h"
#include "const_constexpr_volatile.h"


int main() {
	literals_exercise();
	undefined_behaviour_example();
	automatic_type_deduction_sample_exercise();
	decltype_example();
	automatic_type_deduction_exercise_one();
	example_bad_casting();
	example_static_cast();
	const_cast_example();
	reinterpret_cast_example();
	type_information_example();
	initializer_list_example();
	constexpr_exercise_one();
	volatile_example();
	return 0;
}