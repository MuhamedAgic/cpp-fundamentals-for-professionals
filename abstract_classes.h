
// exercise abstract classes

// Try it! 
// A class hierarchy is constructed to represent a set of hierarchically organized concepts(only).
// Typically, base classes act as interfaces.
// There are two major uses for hierarchies, often named implementation inheritance and interface inheritance.

// Read the class hierarchy rules in the given links:
// C.120 : Use class hierarchies to represent concepts with inherent hierarchical structure(only)
// C.121 : If a base class is used as an interface, make it a pure abstract class
// C.122 : Use abstract classes as interfaces when the complete separation of interface and implementation is needed

#include <iostream>


class Abstr {
public:
	int pubInt = 1;
	virtual ~Abstr() = 0;
protected:
	int protInt = 2;
private:
	int privInt = 3;
};

class ConcreteOne : public Abstr {
public:
	int onePubInt = 4;
protected:
	int oneProtInt = 5;
private:
	int onePrivInt = 6;
};

class ConcreteTwo : protected Abstr {
public:
	int twoPubInt = 7;
protected:
	int twoProtInt = 8;
private:
	int twoPrivInt = 9;
};

class ConcreteThree : private Abstr {
public:
	int threePubInt = 10;
protected:
	int threeProtInt = 11;
private:
	int threePrivInt = 12;
};


void abstract_classes_exercise_one() {
	//Abstr a;
	//ConcreteOne c1;
	//ConcreteTwo c2;
	//ConcreteThree c3;
	
	//std::cout << c1.onePubInt << std::endl;
	//std::cout << c1.oneProtInt << std::endl;
	//std::cout << c1.onePrivInt << std::endl;

	//std::cout << c2.onePubInt << std::endl;
	//std::cout << c2.oneProtInt << std::endl;
	//std::cout << c2.onePrivInt << std::endl;
	//std::cout << c2.twoPubInt << std::endl;
	//std::cout << c2.twoProtInt << std::endl;
	//std::cout << c2.twoPrivInt << std::endl;
	//
	//std::cout << c3.onePubInt << std::endl;
	//std::cout << c3.oneProtInt << std::endl;
	//std::cout << c3.onePrivInt << std::endl;
	//std::cout << c3.twoPubInt << std::endl;
	//std::cout << c3.twoProtInt << std::endl;
	//std::cout << c3.twoPrivInt << std::endl;
	//std::cout << c3.threePubInt << std::endl;
	//std::cout << c3.threeProtInt << std::endl;
	//std::cout << c3.threePrivInt << std::endl;	

}


// Only the default constructor is inherited, the copy and move constructor will not be inherited.

// The derived class inherits all the characteristics of the constructors:

// public, protected, and private access specifiers.
// explicit and constexpr declarations.
// Default arguments for parameters of the constructor of a base class will not be inherited.

// The derived class gets an additional constructor, having one parameter for the default argument.
// Constructors with the same parameters as constructors in the derived class will not be inherited.

// By inheriting constructors from the base class, there is the danger of forgetting to initialize the attributes of the derived class.

// constructor inheriting example
class Base {
public:

	Base() = default;
	Base(int i) {
		std::cout << "Base::Base(" << i << ")" << std::endl;
	}

	Base(std::string s) {
		std::cout << "Base::Base(" << s << ")" << std::endl;
	}
};

class Derived : public Base {
public:

	using Base::Base;

	Derived(double d) {
		std::cout << "Derived::Derived(" << d << ")" << std::endl;
	}

};

void example_constructor_inheriting() {
	// In this example, we have created two classes, i.e., Base and Derived. 
	// The Derived class inherits the Base class publicly. 
	// When we call the Derived class object with the keyword using, it calls the relative constructors. 
	// This can be clearly seen in the objects created in the main section. 
	// For integers and strings, it called the Base class constructors and for doubles, it calls the Derived class constructor.
	
	// inheriting Base
	Derived(2011);         // Base::Base(2011)

	// inheriting Base     // Base::Base(C++0x)
	Derived("C++0x");

	// using Derived
	Derived(0.33);         // Derived::Derived(0.33)

}


// exercise two: Inherit public, protected, and private identifiers from a class using constructor inheritance. 
// The constructors inherited from the base class keep their access level. 
// The inherited class restricts them.
// What does that mean for the inherited constructors ?

class BaseExecise {
public:
	BaseExecise(int a) {
		std::cout << "a: " << a << std::endl;
	};
};

// Make a class which derived Base class publiclly
class DerivedExercisePub : public BaseExecise {
	using BaseExecise::BaseExecise; // relative constructors
};

// Make a class which derived Base class protectedly
class DerivedExerciseProt : protected BaseExecise {
	using BaseExecise::BaseExecise; // relative constructors

};

// Make a class which derived Base class privately
class DerivedExercisePriv : private BaseExecise {
	using BaseExecise::BaseExecise; // relative constructors

};

void constructor_inheritance_exercise() {
	DerivedExercisePub a(5);
	DerivedExerciseProt b(6);
	DerivedExercisePriv c(7);

	// Call the objects of the above classes here
}

// exercise succesfull!

// Sequence followed by destructor calls 
// When we(directly or indirectly) call a destructor, a series of destructor calls may be triggered.
// This guarantees that each base object is properly destructed.
// The sequence of destructor calls starts with the most derived class and ends with the base class.


//struct A {};
//struct B : A {};
//struct C : B {};
//C* c = new C;          // A -> B -> C
//delete c;              // ~C -> ~B -> ~A


// exercise
// Which initialization order of the attributes of a class is guaranteed ?
// The order of their declaration or the invocation order in the constructor.
// Discuss the consequences of each possibility.

// answer: i think that it depens if a initializer list is used or not in the construcor?
// if an initializer list is used, order of declaration
// if the values as initialized in the constructor body, then invocation order in constructor i think

// When destructing an object via a pointer or a reference to a base class, the destructors must be virtual.


// To override a method, the signature of the overridden method of the base class has to match exactly. 
// Although this sounds easy in theory, it is often not in practice. 
// If the signature of the method does not match exactly, the program will compile but have the wrong behavior… 
// A different method than intended will be invoked.


// exercise: Refactor it with the help of override and final.


class Sort {
public:
	virtual void processData() final { // in the solution they make this final
		readData();
		sortData();
		writeData();
	}
private:
	virtual void readData() {}
	virtual void sortData() = 0;
	virtual void writeData() {}
};


// Try using final and override

class QuickSort : public Sort {
private:
	void readData() override { // adding override here, function signatures match
		std::cout << "readData" << std::endl;
	}
	void sortData() override {
		std::cout << "sortData" << std::endl;
	}
	void writeData() override {
		std::cout << "writeData" << std::endl;
	}
};

class BubbleSort : public Sort{
private:
	void readData() override { // adding override here, function signatures match
		std::cout << "readDataBubble" << std::endl;
	}
	void sortData() override {
		std::cout << "sortDataBubble" << std::endl;
	}
	void writeData() override {
		std::cout << "writeDataBubble" << std::endl;
	}
};


void override_final_exercise() {

	std::cout << std::endl;

	Sort* sort = new QuickSort;
	sort->processData();

	std::cout << "Adress of sort: " << sort << std::endl;

	delete sort;
	sort = nullptr;

	sort = new BubbleSort;
	sort->processData();

	std::cout << "Adress of sort: " << sort << std::endl;


	std::cout << std::endl;

}


// the diamond problem
// The diamond problem is an ambiguity that arises when two classes B and C inherit from A, and class D inherits from both B and C. 
// If there is a method in A that B and C have overridden, and D does not override it, then which version of the method does D inherit: that of B, or that of C?

// Ambiguous calls to members can be resolved by using the scope operator.

// multiple inheritance example, diamond

class MultInherAccount {
public:

	MultInherAccount(double amt) :amount(amt) {}

	double getBalance() const {
		return amount;
	}

private:
	double amount;
};

class MultInherBankAccount : public MultInherAccount {
public:
	MultInherBankAccount(double amt) : MultInherAccount(amt) {}
};

class MultInherWireAccount : public MultInherAccount {
public:
	MultInherWireAccount(double amt) : MultInherAccount(amt) {}
};

class MultInherCheckingAccount : public MultInherBankAccount, public MultInherWireAccount {
public:
	MultInherCheckingAccount(double amt) : MultInherBankAccount(amt), MultInherWireAccount(amt) {}
};

void multiple_inheritance_example() {

	std::cout << std::endl;

	MultInherCheckingAccount checkAccount(100.0);
	// checkAccount.getBalance();         // ERROR

	// with scope operator ::, it knows which one to call from one of the base classes
	std::cout << "checkAccount.MultInherBankAccount::getBalance(): " << checkAccount.MultInherBankAccount::getBalance() << std::endl;
	std::cout << "checkAccount.MultInherWireAccount::getBalance(): " << checkAccount.MultInherWireAccount::getBalance() << std::endl;

	std::cout << std::endl;

}


// we can also virtually inherit from Account class
// By inheriting these classes virtually, we can now access the checkAccount.getBalance() method of the Account class.

// so // checkAccount.getBalance();         // ERROR, would work