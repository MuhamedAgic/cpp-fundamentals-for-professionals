

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


void template_parameters_exercise() {
	// uncomment these lines after implementing codes

	/*
	AcceptChar<'c'> acceptChar;
	AcceptFunction< myFunc> acceptFunction;
	AcceptReference< arr > acceptReference;
	AcceptNullptr< nullptr > acceptNullptr;
	*/
}

