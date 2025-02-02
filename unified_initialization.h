// Narrowing, or more precisely narrowing conversion, is an implicit conversion of arithmetic values from one type to another. 
// This can cause a loss of accuracy, which can be extremely dangerous.
// The following example shows the issue with the classical way of initializing fundamental types.
// The compiler presents a warning, yet the implicit conversions are performed nonetheless, resulting in data loss.
// It doesn’t matter whether we use direct initialization or assignment

#include <iostream>
#include <unordered_map>
#include <set>
#include <array>
#include <unordered_set>


void example_warning() {
	char c1(999);
	char c2 = 999;
	std::cout << "c1: " << c1 << std::endl;
	std::cout << "c2: " << c2 << std::endl;

	int i1(3.14);
	int i2 = 3.14;
	std::cout << "i1: " << i1 << std::endl;
	std::cout << "i2: " << i2 << std::endl;

	//The output of the program shows two issues:
	//The int literal, 999, doesn’t fit into the type char.
	//The double literal, 3.14, doesn’t fit into the int type.
	//Such an issue is not possible with{} - initialization.
}


// pro tip: Compile the program in such a way that narrowing is an error.
// Special Rule: If we use automatic type deduction with auto in combination with an {}-initialization, we will get a std::initializer_list in C++14.

// initializer list example
class MyData {
public:

	MyData(std::string, int) {       // classical constructor
		std::cout << "MyData(std::string, int)" << std::endl;
	}

	MyData(int, int) {       // classical constructor
		std::cout << "MyData(int, int)" << std::endl;
	}

	MyData(std::initializer_list<int>) {         // sequence constructor
		std::cout << "MyData(std::initializer_list<int>)" << std::endl;
	}
};

template<typename T>
void printInitializerList(std::initializer_list<T> inList) {
	for (auto& e : inList) std::cout << e << " ";
}

void initializer_list_example() {

	std::cout << std::endl;

	// sequence constructor has a higher priority
	MyData{ 1, 2 };

	// invoke the classical constructor explicitly
	MyData(1, 2);

	// use the classical constructor
	MyData{ "dummy", 2 };

	std::cout << std::endl;

	// print the initializer list of ints
	printInitializerList({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });

	std::cout << std::endl;

	// print the initializer list of strings
	printInitializerList({ "Only", "for", "testing", "purpose." });

	std::cout << "\n\n";

}

// examples
struct MyStruct {
	int x;
	double y;
};

class MyClass {
public:
	int x;
	double y;
};

struct Telephone {
	std::string name;
	int number;
};

Telephone getTelephone() {
	// Telephone("Rainer Grimm", 12345) created
	return { "Rainer Grimm", 12345 };
}

struct MyArray {
public:
	MyArray() : data{ 1, 2, 3, 4, 5 } {}
private:
	const int data[5];
};

void getVector(const std::vector<int>& v) {
	// some code
}

void examples() {

	// built-in datatypes and strings
	bool b{ true };
	bool b2 = { true };
	int i{ 2011 };
	int i2 = { 2011 };
	std::string s{ "string" };
	std::string s2 = { "string" };

	// struct and class
	MyStruct basic{ 5, 3.2 };
	MyStruct basic2 = { 5, 3.2 };
	MyClass alsoClass{ 5, 3.2 };
	MyClass alsoClass2 = { 5, 3.2 };

	// C-Array
	// dynamic array initialization
	const float* pData = new const float[4] { 1.5, 4, 3.5, 4.5 };

	// STL-Container
	// a vector of 1 element
	std::vector<int> oneElement{ 1 };
	std::vector<int> oneElement2 = { 1 };

	std::unordered_map<std::string, int> um{ {"Dijkstra", 1972}, {"Scott", 1976}, {"Wilkes", 1967}, {"Hamming", 1968} };

	// special cases
	// brace initialization for a std::vector
	getVector({ oneElement[0], 5, 10, 20, 30 });

	// method
	std::vector<int> v{};
	v.insert(v.end(), { 99, 88, -1, 15 });

	// getTelephone returns an initializer list
	Telephone tel(getTelephone());

}

// in cpp-14
//auto a = { 42 };   // std::initializer_list<int>
//auto b{ 42 };     // std::initializer_list<int>
//auto c = { 1, 2 }; // std::initializer_list<int>
//auto d{ 1, 2 };   // std::initializer_list<int>

//in cpp-17
//auto a = { 42 };   // std::initializer_list<int>
//auto b{ 42 };     // int
//auto c = { 1, 2 }; // std::initializer_list<int>
//auto d{ 1, 2 };   // error, too many 

// exercise 1

//Initialize the following containers
//std::array
//std::vector
//std::set
//std::unordered_multiset
//with the{ -10, 5, 1, 4, 5 } initializer list.

void unified_initialization_exercise_one() {
	std::array<int, 5> a = { -10, 5, 1, 4, 5 };
	std::vector<int> b = { -10, 5, 1, 4, 5 };
	std::set<int> c = { -10, 5, 1, 4, 5 };
	std::unordered_multiset<int> d = { -10, 5, 1, 4, 5 };
}

