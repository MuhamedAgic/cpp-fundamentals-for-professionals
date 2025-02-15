#include <iostream>

#include "literals.h"
#include "types.h"
#include "automatic_type_deduction.h"
#include "casts.h"
#include "unified_initialization.h"
#include "const_constexpr_volatile.h"
#include "move_semantics_perfect_forwarding.h"
#include "functions.h"
#include "classes_and_objects.h"
#include "abstract_classes.h"


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
	lr_value_example();
	copy_example();
	move_example();
	move_semantics_exercise_one();
	perfect_forwarding_exercise_one();
	closure_with_lambdas_example();
	functions_exercise_one_fix();
	initializer_for_instances_exercise_one();
	constructor_delegation_example();
	delete_exercise_one();
	explicit_conversion_exercise_one();
	func_obj_example();
	call_operator_exercise_one();
	union_example();
	abstract_classes_exercise_one();
	example_constructor_inheriting();
	constructor_inheritance_exercise();
	override_final_exercise();
	multiple_inheritance_example();
	return 0;
}