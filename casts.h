// cast types
// static cast
// dynamic cast
// const cast
// reinterpret cast

// avoid c-style casts

#include <iostream>

void example_bad_casting() {
	double d = 2;
	auto p = (long*)&d;
	auto q = (long long*)&d;
	std::cout << d << ' ' << *p << ' ' << *q << '\n';
}

// dynamic cast, cast up or down the inheritance hierarchy
class Account {
public:
	virtual ~Account() = default;
};

class BankAccount : virtual public Account {};

class WireAccount : virtual public Account {};

class CheckingAccount : public BankAccount, public WireAccount {};

class SavingAccount : public BankAccount, public WireAccount {};

void dynamic_cast_example() {
	Account* a = nullptr;
	BankAccount* b = nullptr;
	WireAccount* w = nullptr;
	SavingAccount* s = nullptr;

	CheckingAccount c;

	a = dynamic_cast<Account*> (&c);                        // upcast
	a = &c;                                                 // upcast

	b = dynamic_cast<BankAccount*>(a);                      // downcast
	w = dynamic_cast<WireAccount*>(b);                      // crosscast
	s = dynamic_cast<SavingAccount*>(a);                    // downcast
}

// static_cast is the simplest casting operator and is used for simple conversions.

// It can only perform all the conversions that are well - defined by the compiler.
// For example, a string to integer cast won’t work.
// It allows bidirectional conversion between related data types such as:
// - pointer types in class hierarchies
// - integrals and floating - point numbers
// - integrals and enumerations
// - static_cast cannot be used with polymorphic types.

//Unlike dynamic_cast, a static_cast is performed during compile time.

class AnotherAccount {};
class AnotherBankAccount : public AnotherAccount {};

enum Color {
	red,
	blue,
	green
};

void example_static_cast() {

	std::cout << std::endl;

	AnotherAccount* a = nullptr;
	AnotherBankAccount* b = nullptr;

	a = static_cast<AnotherAccount*> (b);                         // upcast
	a = b;                                                 // upcast

	b = static_cast<AnotherBankAccount*>(a);                      // downcast

	int i{ 2 };
	Color col = static_cast<Color>(i);
	std::cout << "i: " << i << std::endl;
	std::cout << "col: " << col << std::endl;

	int i2 = static_cast<int>(3.14);
	std::cout << "i2: " << i2 << std::endl;

	std::cout << std::endl;

}

void const_cast_example() {
	std::cout << std::endl;

	int i{ 2011 };
	const int* constI = const_cast<const int*>(&i); // A const int pointer for an int
	int* nonConstI = const_cast<int*>(constI); // Casting to an int pointer
	*nonConstI = 9000;

	std::cout << "i: " << i << std::endl;

	std::cout << std::endl;

	std::cout << "typeid(constI).name(): " << typeid(constI).name() << std::endl;
	std::cout << "typeid(nonConstI).name(): " << typeid(nonConstI).name() << std::endl;

	std::cout << std::endl;
}

// reinterpret_cast allows us to convert a pointer of a particular type to a pointer of any other type, regardless of whether the types are related or not.
// It also allows conversion between a pointer and an integral.
// reinterpret_cast guarantees that if a pointer is cast into another type, casting it back would return the original value.
// The use of reinterpret_cast is not recommended as it does not take any safety measures before converting between types.
// This can result in faulty or accidental conversions that could harm the code.

void reinterpret_cast_example() {
	double* myDouble = new double(3.14);
	std::cout << *myDouble << std::endl;

	void* myVoid = reinterpret_cast<void*>(myDouble);

	double* myDouble1 = reinterpret_cast<double*>(myVoid); // Original value retrieved
	std::cout << *myDouble1 << std::endl;
}

void type_information_example() {

	std::cout << std::endl;

	// types
	if (typeid(int) == typeid(long long)) {
		std::cout << "The types int and long long are the same" << std::endl;
	}
	else {
		std::cout << "The types int and long long are different" << std::endl;
	}
	std::cout << "typeid(int).name(): " << typeid(int).name() << std::endl;
	std::cout << "typeid(long long).name(): " << typeid(long long).name() << std::endl;

	std::cout << std::endl;

	// variables
	int i{ 2011 };
	int long long il{ 2011 };

	std::cout << "typeid(i).name(): " << typeid(i).name() << std::endl;
	std::cout << "typeid(il).name(): " << typeid(il).name() << std::endl;

	if (typeid(i) == typeid(il)) {
		std::cout << "The variables i and il are of the same type" << std::endl;
	}
	else {
		std::cout << "The variables i and il are of different types" << std::endl;
	}

	std::cout << std::endl;
}