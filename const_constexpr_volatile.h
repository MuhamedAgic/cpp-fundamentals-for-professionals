#include <iostream>

void example_one() {
	int i = 2011;
	int const* ip = &i; // const before *, so variable is const, not the pointer
	//*ip = 2012; // ERROR

	int j = 2012;
	ip = &j;
}

void const_pointer_example() {
	int i = 2011;
	int j = 2012;
	int* const p = &i; // const after *, so pointer is const, variable can be changed
	//p = &j; // ERROR

	*p = 2015;
}

void const_var_const_ptr_example() {
	int i = 100;
	int j = 200;
	const int* const p = &i;
	//*p = i; // ERROR 
	//p = &j; // ERROR
}

// constexpr functions in C++14
// can have variables that have to be initialized by a constant expression.
// can have loops.
// cannot have static or thread_local data.
// can have conditional jump instructions or loop instructions.
// can have more than one instruction.

// Pure functions
// We can execute constexpr functions at runtime.
// If we use the return value of a constexpr function in a constant expression, the compiler will perform the function at compile time.
// So then, is there a reason to perform a constexpr function at runtime? 
// Of course! You have the constexpr function so we can use it at runtime.
// But there is another, much more convincing reason.
// 
// A constexpr function can potentially be performed at compile - time.
// There is no state at compile time, since we are in a pure functional sublanguage of the imperative programming language C++.
// In particular, this means that, at compile time, executed functions have to be pure functions.
// When we use this constexpr function at runtime the function stays pure.
// Pure functions are functions that always return the same result when given the same arguments.
// Pure functions are like infinitely large tables from which we get our value.
// The guarantee that an expression always returns the same result when given the same arguments is called referential transparency.


// examples
constexpr int square(int x) { return x * x; }
constexpr int squareToSquare(int x) { return square(square(x)); }

void example() {
	std::cout << std::endl;

	static_assert(square(10) == 100, "you calculated it wrong");
	static_assert(squareToSquare(10) == 10000, "you calculated it wrong");

	std::cout << "square(10) = " << square(10) << std::endl;
	std::cout << "squareToSquare(10) = " << squareToSquare(10) << std::endl;
	constexpr int constExpr = square(10);

	int arrayClassic[100];
	int arrayNewWithConstExpression[constExpr];
	int arrayNewWithConstExpressioFunction[square(10)];

	std::cout << std::endl;
}


// exercise 1
// Use the structure, MyDouble, in our program. 
// How can we check that instances of MyDouble will be created at compile-time?

struct MyDouble {
	double myVal;
	constexpr MyDouble(double v) : myVal(v) {}
	constexpr double getVal() const { 
		return myVal; 
	}
};

void constexpr_exercise_one() {
	constexpr MyDouble a(3.14);
	static_assert(a.getVal() == 3.14, "failed"); // try 3.15
}

// exercise 2
// What will happen if we instantiate MyDouble with a non-constant expression?

void constexpr_exercise_two() {
	MyDouble a(3.14);
	//static_assert(a.getVal() == 3.14, "failed"); // ERROR, expression must have constant value
}


// volatile
// The volatile variable is one whose value may change due to an external event.

volatile int x = 0;
volatile int y = 0;

void writing() {
	x = 2000;
	y = 11;
}

void reading() {
	std::cout << "y: " << y << " ";
	std::cout << "x: " << x << std::endl;
}

void volatile_example() {
	std::thread thread1(writing);
	std::thread thread2(reading);
	thread1.join();
	thread2.join();
};