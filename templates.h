

#include <iostream>

// exercise one: Implement a function which calculates 2^10 in the program. 
// Try using templates to implement the function.

template <typename T>
int power(const T& base, const T& exp) {
	T result = 1;
	for (size_t i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
}

// after seeing some solutions
template <typename T>
constexpr T power_v2(const T& base, const T& exp) {
	T result = 1;
	for (size_t i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
}


void exercise_one() {
	int base = 2;
	int exp = 3;
	int res = power(base, exp);
	std::cout << "2 to the power of 3: " << res << std::endl;


	double res2 = power<long>(3, 3);
	std::cout << "3 to the power of 3: " << res2 << std::endl;


	constexpr long res3 = power_v2<long>(3, 3);
	std::cout << "constexpr 3 to the power of 3: " << res3 << std::endl;
}

// Some solutions

// Using Template Arguments

template<int m, int n>
struct Power {
	static int const value = m * Power<m, n - 1>::value;
};

template<int m>
struct Power<m, 0> {
	static int const value = 1;
};

// Using Template Arguments and Function Arguments 

template<int n>
int power(int m) {
	return m * power<n - 1>(m);
}

template<>
int power<1>(int m) {
	return m;
}

template<>
int power<0>(int m) {
	return 1;
}

// Template functions from base class are not automaticly available in the derived class!

// There are three ways to make a method from the derived class template available.
// 3 Solutions:
// Qualification via this pointer : this->func()
// Introducing the name using Base<T>::func
// Full qualified access Base<T>::func()

// Alias templates, aka template typedefs, allow us to give a name to partially bound templates. 
// An example of partial specialization from templates is given below:

template <typename T, int Line, int Col> class Matrix {
	//...
};

template <typename T, int Line>
using Square = Matrix<T, Line, Line>;

template <typename T, int Line>
using Vector = Matrix<T, Line, 1>;

Matrix<int, 5, 3> ma;
Square<double, 4> sq;
Vector<char, 5> vec;

// Example: inheritance in class templates


template <typename T>
class BaseTempl {
public:
	void func1() const {
		std::cout << "func1()" << std::endl;
	}
	void func2() const {
		std::cout << "func2()" << std::endl;
	}
	void func3() const {
		std::cout << "func3()" << std::endl;
	}
};

template <typename T>
class DerivedTempl : public BaseTempl<T> {
public:
	using BaseTempl<T>::func2;

	void callAllBaseFunctions() {
		this->func1();
		func2();
		BaseTempl<T>::func3();
	}
};

void template_inheritance_example() {
	std::cout << std::endl;

	DerivedTempl<int> derived;
	derived.callAllBaseFunctions();

	std::cout << std::endl;
}


// Make the name dependent: The call this->func1 in line 25 is dependent. 
// In this case, the name lookup will consider all base classes.

// Introduce the name into the current scope:
// The expression using Base<T>::func2(line 22) introduces func2 into the current scope.

// Call the name fully qualified:
// Calling func3 fully qualified(line 27) will break virtual dispatch and may cause new surprises.

// class templates exercise

// Uncomment the final assignment doubleArray = strArray in line 41 and use the function 
// static_assert in combination with the function std::is_convertible to catch 
// the erroneous instantiation at compile-time.


template <typename T, int N>
class Array {

public:
	Array() = default;

	template <typename T2>
	Array<T, N>& operator=(const Array<T2, N>& arr) {
		// write your code here
		// uncomment line 41 to check if your code runs fine
		// The solution, now when its not convertible, it fails at compile time
		static_assert(std::is_convertible<T, T2>::value, "Cannot source type to destination type"); // SOLUTION
		elem.clear();
		elem.insert(elem.begin(), arr.elem.begin(), arr.elem.end());
		return *this;
	}

	int getSize() const;

	std::vector<T> elem;
};

template <typename T, int N>
int Array<T, N>::getSize() const {
	return N;
}

void class_template_exercise() {

	Array<double, 10> doubleArray{};
	Array<int, 10> intArray{};

	doubleArray = intArray;

	Array<std::string, 10> strArray{};
	Array<int, 100> bigIntArray{};

	//doubleArray= strArray;            // ERROR: cannot convert ‘const std::basic_string<char>’ to ‘double’
	 //doubleArray= bigIntArray;         // ERROR: no match for ‘operator=’ in ‘doubleArray = bigIntArray

}

// === General Friends ===
// A class or a class template can grant friendship to each instance of 
// a class template or a function template.


template <typename T> int myFriendFunction(T);

template <typename T> class MyFriend;

template <typename T>
class GrantingGeneralFriendshipAsClassTemplate {
	template <typename U> friend int myFriendFunction(U);
	template <typename U> friend class MyFriend;
};


// When a class template grants friendship to a template using the same template parameter name, 
// the friendship is granted only for the same types. 
// If the intention is to grant friendship for any type of template parameter, 
// the template parameter names should be different.

// === Special Friends ===

//A special friendship is a friendship that depends on the type of the template parameter.

template <typename T> int myFriendFunction(T);
template <typename T> class MyFriend;

template <typename T>
class GrantingSpecialFriendshipAsClassTemplate {
	friend int myFriendFunction<>(double);
	friend class MyFriend<int>;
	friend class MyFriend<T>;
};

// If the name of the template parameter is identical to the name of the 
// template parameter granting the friendship, 
// the friendship will be between instances of the same type.



// === Friends exercise ===

// Make the public member elem a private member of Array. 
// How does that affect the implementation of the assignment operator?

// Uncomment the code in the exercise function to see what happens.

template <typename T, int N>
class ArrayFriendsExercise {

public:
	ArrayFriendsExercise() = default;

	template <typename T2, int M> friend class ArrayFriendsExercise; // SOLUTION

	template <typename T2>
	ArrayFriendsExercise<T, N>& operator=(const ArrayFriendsExercise<T2, N>& arr) {
		static_assert(std::is_convertible<T2, T>::value, "Cannot convert source type to destination type!");
		elem.clear();
		elem.insert(elem.begin(), arr.elem.begin(), arr.elem.end());
		return *this;
	}

	int getSize() const;
	// you need to make the `elem` private and then run it
private:
	std::vector<T> elem;
};

template <typename T, int N>
int ArrayFriendsExercise<T, N>::getSize() const {
	return N;
}


void friends_exercise() {
	// uncomment these line after the above implementation

	ArrayFriendsExercise<double, 10> doubleArray{};
	ArrayFriendsExercise<int, 10> intArray{};
	doubleArray = intArray;
}

// In the code above, we have created an Array class in which we have defined a 
// method = which copies the entries of integer array to double array. 
// The getSize function returns the size of the array passed in the argument. 
// Template classes with different template arguments are considered of different types, 
// which is why Array<int, 10> and Array<double, 10> aren’t able to access each other. 
// And that’s why the Array template class has to be declared a friend of itself.

// To access the private elem of arr in line 263, 
// class Array is a friend of the class Array in line 250.


// === Template parameters exercise ===

// Implement four different class templates that accept an 
// integral, pointer, reference, or a nullptr as a non-type parameter. 
// Also, display the parameter’s type.

// Write class templates for given commented code
template <char T>
class AcceptChar {
public:
	AcceptChar() {
		std::cout << "Accept char: " << typeid(T).name() << std::endl;
	}
};

template <int(&arr)[5]>
class AcceptReference {
public:
	AcceptReference() {
		std::cout << "Accept reference: " << typeid(arr).name() << std::endl;
	}
};

template <std::nullptr_t T>
class AcceptNullptr {
public:
	AcceptNullptr() {
		std::cout << "Accept nullptr: " << typeid(T).name() << std::endl;
	}
};

template <int(*func)(int)>
class AcceptFunction {
	public:
	AcceptFunction() {
		std::cout << "Accept function: " << typeid(func).name() << std::endl;
	}
};


int myFunc(int) { return 2011; };
int arr[5];

void template_parameters_exercise() {
	AcceptChar<'c'> acceptChar;
	AcceptFunction<myFunc> acceptFunction;
	AcceptReference<arr> acceptReference;
	AcceptNullptr<nullptr> acceptNullptr;	
}


// EXPLANATION
// We have created four different class templates which include 
// AcceptChar, AcceptFunction, AcceptReference, and AcceptNull
// Each class template accepts a different non-type. 
// To verify all, we have declared a character variable, 
// a reference to an array, a function, and nullptr.
// We identify their types using the operator typeid.


// Variadic templates

template<typename T, typename ... Args>
T createT(Args&& ... args) {
	return T(std::forward<Args>(args) ...);
}

struct MyStructVarTemp {
	MyStructVarTemp(int&, double&, double&&) {}
	friend std::ostream& operator<< (std::ostream& out, const MyStructVarTemp&) {
		out << "MyStruct" << std::endl;
		return out;
	}
};

void variadic_templates_example() {

	std::cout << std::endl;

	double myDouble = createT<double>();
	std::cout << "myDouble: " << myDouble << std::endl;

	int myInt = createT<int>(1);
	std::cout << "myInt: " << myInt << std::endl;

	std::string myString = createT<std::string>("My String");
	std::cout << "myString: " << myString << std::endl;

	MyStructVarTemp myStruct = createT<MyStructVarTemp>(myInt, myDouble, 3.14);
	std::cout << "myStruct: " << myStruct << std::endl;

	std::cout << std::endl;
}

// In the example above, we have created a createT function which invokes the constructor T 
// with the arguments args. If there is no value passed, it invokes the default constructor. 
// The magic of the factory function createT is that it can invoke each constructor. 
// Thanks to perfect forwarding, each value can be used such as an lvalue or an rvalue; 
// thanks to parameter packs, any number of arguments can be used. In the case of MyStruct, 
// a constructor that requires three arguments is used.

// The pattern of the function template createT is exactly the pattern factory functions such as 
// std::make_unique, std::make_shared, std::make_pair, or std::make_tuple use.


// exercise
// The class Matrix holds its values in the container Cont.

// Cont should have a default argument std::vector.
// Instantiate myIntVec and myDoubleVec without specifying the container explicitly.
#include <list>
#include <vector>
#include <initializer_list>

template <typename T, template <typename, typename> class Cont = std::vector> // check! Cont = std::vector 
class MatrixTempArgsExercise {
public:
	explicit MatrixTempArgsExercise(std::initializer_list<T> inList) : data(inList) {
		for (auto d : data) std::cout << d << " ";
	}
	int getSize() const {
		return data.size();
	}

private:
	Cont<T, std::allocator<T>> data;

};

void template_arguments_exercise() {

	std::cout << std::endl;

	// Define myIntVec and myDoubleVec without specifying containers explicitly
	// Call getSize() function on it to check the result

	MatrixTempArgsExercise<std::string, std::list> myStringList{ "one", "two", "three", "four" };
	std::cout << std::endl;
	std::cout << "myStringList.getSize(): " << myStringList.getSize() << std::endl;

	MatrixTempArgsExercise<int> myIntVec{ 1, 2, 3, 4 }; // no need for MatrixTempArgsExercise<int, std::vector>
	std::cout << std::endl;
	std::cout << "myStringList.getSize(): " << myIntVec.getSize() << std::endl;

	MatrixTempArgsExercise<double> myDoubleVec{ 1.0, 2.0, 3.0, 4.0 }; // no need for MatrixTempArgsExercise<double, std::vector>
	std::cout << std::endl;
	std::cout << "myStringList.getSize(): " << myDoubleVec.getSize() << std::endl;

	std::cout << std::endl;

}


#include <type_traits>

using namespace std;

template <typename T>
void getPrimaryTypeCategory() {

	cout << boolalpha << endl;

	cout << "is_void<T>::value: " << is_void<T>::value << endl;
	cout << "is_integral<T>::value: " << is_integral<T>::value << endl;
	cout << "is_floating_point<T>::value: " << is_floating_point<T>::value << endl;
	cout << "is_array<T>::value: " << is_array<T>::value << endl;
	cout << "is_pointer<T>::value: " << is_pointer<T>::value << endl;
	cout << "is_reference<T>::value: " << is_reference<T>::value << endl;
	cout << "is_member_object_pointer<T>::value: " << is_member_object_pointer<T>::value << endl;
	cout << "is_member_function_pointer<T>::value: " << is_member_function_pointer<T>::value << endl;
	cout << "is_enum<T>::value: " << is_enum<T>::value << endl;
	cout << "is_union<T>::value: " << is_union<T>::value << endl;
	cout << "is_class<T>::value: " << is_class<T>::value << endl;
	cout << "is_function<T>::value: " << is_function<T>::value << endl;
	cout << "is_lvalue_reference<T>::value: " << is_lvalue_reference<T>::value << endl;
	cout << "is_rvalue_reference<T>::value: " << is_rvalue_reference<T>::value << endl;

	cout << endl;

}

void getPrimaryTypeCategoryExample() {
	getPrimaryTypeCategory<void>();
}


// We have used the type_traits library, which detects, at compile-time, 
// which primary type category void (line 13) belongs to. 
// The primary type categories are complete and exclusive. 
// This means each type belongs to exactly one primary type category. 
// For example, void returns true for the type-trait std::is_void and false for 
// all the other type categories.


// exercise specialization

// The class template Type in the code below returns the name unknown to each type.

// Use the class template Type as a starting point to write a type introspection system 
// with the help of partial and full specialization.
// We’ll need to write code for int, double, an arbitrary 
// classes named Account, pointer, const, and string.

template<typename T>
struct Type {
	std::string getName() const {
		return "unknown";
		//return typeid(T).name(); // solution? No
	}
};

template<>
struct Type<int> {
	std::string getName() const {
		return "int";
	}
};

template<>
struct Type<double> {
	std::string getName() const {
		return "double";
	}
};

template<>
struct Type<float> {
	std::string getName() const {
		return "float";
	}
};

template<typename T>
struct Type<const T> {
	std::string getName() const {
		return "const";
	}
};

template<typename T>
struct Type<T*> {
	std::string getName() const {
		return "pointer";
	}
};

void specialization_exercise() {

	std::cout << std::boolalpha << std::endl;

	// call objects for each defined templetes here
	Type<int> tInt;
	std::cout << "tInt.getName(): " << tInt.getName() << std::endl;

	Type<double> tDouble;
	std::cout << "tDouble.getName(): " << tDouble.getName() << std::endl;

	Type <std::string> tString;
	std::cout << "tString.getName(): " << tString.getName() << std::endl;

	Type <int*> tPointer;
	std::cout << "tPointer.getName(): " << tPointer.getName() << std::endl;

	Type <const long> tSomeConst;
	std::cout << "tSomeConst.getName(): " << tSomeConst.getName() << std::endl;

	// An example of float is given below which returned "unknown"
	Type<float> tFloat;
	std::cout << "tFloat.getName(): " << tFloat.getName() << std::endl;

	std::cout << std::endl;

}



// CRTP: The acronym CRTP stands for the C++ idiom Curiously Recurring Template Pattern. 
// It is a technique in C++ in which a Derived class derives from a class template Base. 
// The key is that Base has Derived as a template argument.


template<class Derived>
class Relational {};

// Relational Operators

template <class Derived>
bool operator > (Relational<Derived> const& op1, Relational<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return d2 < d1;
}

template <class Derived>
bool operator == (Relational<Derived> const& op1, Relational<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return !(d1 < d2) && !(d2 < d1);
}

template <class Derived>
bool operator != (Relational<Derived> const& op1, Relational<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return (d1 < d2) || (d2 < d1);
}

template <class Derived>
bool operator <= (Relational<Derived> const& op1, Relational<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return (d1 < d2) || (d1 == d2);
}

template <class Derived>
bool operator >= (Relational<Derived> const& op1, Relational<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return (d1 > d2) || (d1 == d2);
}

// Apple

class Apple :public Relational<Apple> {
public:
	explicit Apple(int s) : size{ s } {};
	friend bool operator < (Apple const& a1, Apple const& a2) {
		return a1.size < a2.size;
	}
private:
	int size;
};

// Man

class Man :public Relational<Man> {
public:
	explicit Man(const std::string& n) : name{ n } {}
	friend bool operator < (Man const& m1, Man const& m2) {
		return m1.name < m2.name;
	}
private:
	std::string name;
};

void CRTP_example() {

	std::cout << std::boolalpha << std::endl;

	Apple apple1{ 5 };
	Apple apple2{ 10 };
	std::cout << "apple1 < apple2: " << (apple1 < apple2) << std::endl;
	std::cout << "apple1 > apple2: " << (apple1 > apple2) << std::endl;
	std::cout << "apple1 == apple2: " << (apple1 == apple2) << std::endl;
	std::cout << "apple1 != apple2: " << (apple1 != apple2) << std::endl;
	std::cout << "apple1 <= apple2: " << (apple1 <= apple2) << std::endl;
	std::cout << "apple1 >= apple2: " << (apple1 >= apple2) << std::endl;

	std::cout << std::endl;

	Man man1{ "grimm" };
	Man man2{ "jaud" };
	std::cout << "man1 < man2: " << (man1 < man2) << std::endl;
	std::cout << "man1 > man2: " << (man1 > man2) << std::endl;
	std::cout << "man1 == man2: " << (man1 == man2) << std::endl;
	std::cout << "man1 != man2: " << (man1 != man2) << std::endl;
	std::cout << "man1 <= man2: " << (man1 <= man2) << std::endl;
	std::cout << "man1 >= man2: " << (man1 >= man2) << std::endl;

	std::cout << std::endl;

}

// mixins with crtp

// We have implemented, for the classes Apple and Man, the smaller operators separately. 
// The classes Man and Apple are publicly derived from the class Relational<Man> and 
// Ralational<Apple>. For classes of the kind Relational, we have implemented the greater than 
// operator >, the equality operator ==, the not equal to operator !=, 
// the less than or equal to operator <= and the greater than or equal to operator >= 
// The less than or equal (<=) and greater than or equal to (>=) operators used 
// the equality operator ==. All these operators convert their operands: 
// Derived const&: Derived const& d1 = static_cast<Derived const&>(op1).


// example static polymorphism

template <typename DerivedStatPolyExample>
struct BaseStatPolyExample {
	void Interface() {
		static_cast<DerivedStatPolyExample*>(this)->implementation();
	}

	void implementation() {
		std::cout << "Implementation Base" << std::endl;
	}
};

struct Derived1 : BaseStatPolyExample<Derived1> {
	void implementation() {
		std::cout << "Implementation Derived1" << std::endl;
	}
};

struct Derived2 : BaseStatPolyExample<Derived2> {
	void implementation() {
		std::cout << "Implementation Derived2" << std::endl;
	}
};

struct Derived3 : BaseStatPolyExample<Derived3> {};

template <typename T>
void execute(T& base) {
	base.Interface();
}

void example_static_polymorphism() {

	std::cout << std::endl;

	Derived1 d1;
	execute(d1);

	Derived2 d2;
	execute(d2);

	Derived3 d3;
	execute(d3);

	std::cout << std::endl;

}

// We have used static polymorphism in the function template execute. 
// We then invoked the method base.Interface on each base argument. 
// These method Base::Interface, is the key point of the CRTP idiom. 
// The methods dispatch to the implementation of 
// the derived class: static_cast<Derived*>(this)->implementation() which is possible 
// because the method will be instantiated when called. 
// At this point in time, the derived classes Derived1, Derived2, and Derived3 are fully defined. 
// Therefore, the method Base::Interface can use the details of its derived classes. 
// The method Base::implementation is especially interesting. 
// This method works as the default implementation for the static polymorphism for the class Derived3.


// crtp exercise:
// Extend the given piece of code with a Person class. 
// A Person should have a first and last name.

// We need to create two objects of the Person class and compare these objects using 
// relational operators.

template<class Derived>
class RelationalExercise {};

// Relational Operators

template <class Derived>
bool operator > (RelationalExercise<Derived> const& op1, RelationalExercise<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return d2 < d1;
}

template <class Derived>
bool operator == (RelationalExercise<Derived> const& op1, RelationalExercise<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return !(d1 < d2) && !(d2 < d1);
}

template <class Derived>
bool operator != (RelationalExercise<Derived> const& op1, RelationalExercise<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return (d1 < d2) || (d2 < d1);
}

template <class Derived>
bool operator <= (RelationalExercise<Derived> const& op1, RelationalExercise<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return (d1 < d2) || (d1 == d2);
}

template <class Derived>
bool operator >= (RelationalExercise<Derived> const& op1, RelationalExercise<Derived> const& op2) {
	Derived const& d1 = static_cast<Derived const&>(op1);
	Derived const& d2 = static_cast<Derived const&>(op2);
	return (d1 > d2) || (d1 == d2);
}

// Implement a person class here

// Person
class Person : public RelationalExercise<Person> {
public:
	explicit Person(std::string name) : name{ name } {}
	friend bool operator < (const Person& p1, const Person& p2) {
		return p1.name < p2.name; // geen idee of dit ergens op slaat :) maar geeft niet voor de opdracht
	}


private:
	std::string name;
};

// Apple

class Apple2 :public RelationalExercise<Apple2> {
public:
	explicit Apple2(int s) : size{ s } {};
	friend bool operator < (Apple2 const& a1, Apple2 const& a2) {
		return a1.size < a2.size;
	}
private:
	int size;
};

// Man

class Man2 :public RelationalExercise<Man> {
public:
	explicit Man2(const std::string& n) : name{ n } {}
	friend bool operator < (Man2 const& m1, Man2 const& m2) {
		return m1.name < m2.name;
	}
private:
	std::string name;
};

void crtp_exercise() {

	std::cout << std::boolalpha << std::endl;

	// Call Person class object here checks them for all relational operators
	Person p("Anamaria");
	Person q("Koekoek");

	std::cout << "p < q: " << (p < q) << std::endl;
	std::cout << "p > q: " << (p > q) << std::endl;
	std::cout << "p <= q: " << (p <= q) << std::endl;
	std::cout << "p >= q: " << (p >= q) << std::endl;
	std::cout << "p == q: " << (p == q) << std::endl;
	std::cout << "p != q: " << (p != q) << std::endl;


	std::cout << std::endl;
}

// crtp exercise 2:
// In example 2, how can we prevent a derived class, which has 
// the wrong template parameter: Derived4: Base<Derived3>


template <typename Derived>
struct BaseExercise2 {
	void interface() {
		static_cast<Derived*>(this)->implementation();
	}
	void implementation() {
		std::cout << "Implementation Base" << std::endl;
	}
};

struct Derived7 : BaseExercise2<Derived7> {
	void implementation() {
		std::cout << "Implementation Derived1" << std::endl;
	}
};

struct Derived8 : BaseExercise2<Derived8> {
	void implementation() {
		std::cout << "Implementation Derived2" << std::endl;
	}
};

struct Derived9 : BaseExercise2<Derived9> {};

//template <typename T>
//void execute(T& base) {
//	base.interface();
//}

// Write the struct here
struct Derived4 : BaseExercise2<Derived4> {}; // The Derived4 struct cant have Derived3 as template arg?

void crtp_exercise_two() {

	std::cout << std::endl;

	// call the function here
	Derived4 d4;
	d4.implementation();

	std::cout << std::endl;

}

// The functionality of the program in example 2 of the previous lesson can be implemented in various ways. 
// Implement each variant.

// Case 1: Object-oriented with dynamic polymorphism.

// Implement the functionality here
class OOP_Base {
public:
	explicit OOP_Base() = default;
	explicit OOP_Base(int a) : a(a) {}
	virtual void printSomething() const {
		std::cout << "Base" << std::endl;
	}

private:
	int a;
};

class OOP_deriv : public OOP_Base {
public:
	explicit OOP_deriv(int b) : b(b) {}
	void printSomething() const override{
		std::cout << "Deriv" << std::endl;
	}
private:
	int b;
};




void object_oriented_crtp_exercise_three() {
	// call the function here
	OOP_deriv d(5);
	d.printSomething();
	
}

// Case 2: Just a function template.

void just_func_template_crtp_exercise_three() {
	// call the function here

}


// case 3: To solve this exercise with Concepts, peek into the last chapter of this course. 
// Concepts are a valid and elegant method.

void concept_crtp_exercise_three() {
	// call the function here

}

// case 4: Implement the class ShareMe and use it.

// Objects of the class ShareMe should return an std::shared_ptr to themselves.

void shareme_crtp_exercise_three() {
	// call the function here
	  // After implementing the shareMe class uncomment the code given below

	  /*
	  std::cout << std::endl;

	  // share the same ShareMe object
	  std::shared_ptr<ShareMe> shareMe(new ShareMe);
	  std::shared_ptr<ShareMe> shareMe1= shareMe->getShared();

	  // both resources have the same address
	  std::cout << "Address of resource of shareMe "<< (void*)shareMe.get() << " " << std::endl;
	  std::cout << "Address of resource of shareMe1 "<< (void*)shareMe1.get() << " " << std::endl;

	  // the use_count is 2
	  std::cout << "shareMe.use_count(): "<< shareMe.use_count() << std::endl;
	  std::cout << std::endl;
	  */
}



