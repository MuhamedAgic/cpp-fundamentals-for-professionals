// A function object is an instance of a class for which the call operator, operator (), is overloaded. 
// This means that a function object is an object that behaves like a function. 
// The main difference between a function and a function object is that a function object is an object and can, therefore, have a state.

// a generic lambda is a function template

#include <iostream>

void closure_with_lambdas_example() {
	// The copy variable is captured as a copy. Hence, its value is simply copied and bound to the lambda.
	// In line 11, when the value of copy is altered to "changed", the change isn’t reflected in the lambda() call.This is because lambda() is bound to the original value of copy.
	// For ref, there is the opposite effect, since it is captured as a reference.A change in its value on line 12 is reflected in lambda() as well.
	
	std::cout << std::endl;

	std::string copy = "original";
	std::string ref = "original";
	auto lambda = [copy, &ref] {std::cout << copy << " " << ref << std::endl; };
	lambda();
	copy = "changed";
	ref = "changed";
	lambda();

	std::cout << std::endl;
}

// exercise 1: fix the undefined behavior

// ORIGINAL
std::function<std::string()> makeLambda() {
	const std::string val = "on stack created";
	return [&val] {return val; };
}

void functions_exercise_one() {
	auto bad = makeLambda();
	std::cout << bad();
}

// FIX

std::function<std::string()> makeLambdaFix() {
	const std::string val = "on stack created";
	return [&val] {return val; }; // ERROR, return reference but object cleared
	return [val] {return val; };
	// removing the reference of captures val fixed it
	// because you got a reference but the string was cleared when it exited the scope
}

void functions_exercise_one_fix() {
	auto bad = makeLambdaFix();
	std::cout << bad();
}
