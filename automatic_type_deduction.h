#include <string>
#include <iostream>
#include <chrono>
#include <map>
#include <future>

struct T1 {};

struct T2 {
    int mem;     // Not ok: indeterminate value
public:
    T2() {}
};

struct T3 {
    int mem = 0;     // Not ok: indeterminate value
public:
    T3() {}
};

int n;          //  ok: initialized to 0

void undefined_behaviour_example() {
    std::cout << "undefined behaviour example" << std::endl;

    std::cout << std::endl;

    int n;               // Not ok: indeterminate value
    std::string s;       // ok: Invocation of the default constructor; initialized to "" 
    T1 t1;               // ok: Invocation of the default constructor 
    T2 t2;               // ok: Invocation of the default constructor
    T3 t3;               // ok: Invocation of the default constructor

    // :: is the scope resolution operator, ::n in this case means, take the n from outer scope
    std::cout << "::n " << ::n << std::endl;
    //std::cout << "n: " << n << std::endl; // ERROR
    std::cout << "s: " << s << std::endl;
    std::cout << "T2().mem: " << T2().mem << std::endl;
    std::cout << "T3().mem: " << T3().mem << std::endl;

    std::cout << std::endl;

}

void automatic_type_deduction_sample_exercise() {
    // Exercise 1: Try to replace as many usages of auto as possible.
    std::cout << "replace as many usages of auto as possible" << std::endl;

    std::initializer_list<int> myInts = {1, 2, 3};
    std::initializer_list<int>::iterator myIntBegin = myInts.begin();

    std::map<int, std::string> myMap = { {1, std::string("one")}, {2, std::string("two")} };
    std::map<int, std::string>::iterator myMapBegin = myMap.begin();

    // from solution
    std::function<std::string(const std::string&)> func = [](const std::string& a) { return a; };

    std::future<std::string> futureLambda = std::async([](const std::string& s) {return std::string("Hello ") + s; }, std::string("lambda function."));

    std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();
    // or from solution
    std::chrono::time_point<std::chrono::system_clock> begin_v2 = std::chrono::system_clock::now();

    std::pair<int, std::string> pa = std::make_pair(1, std::string("second"));

    std::tuple<std::string, int, float, bool, char> tup = std::make_tuple(std::string("second"), 4, 1.1, true, 'a');
}


// decltype
// If the expression is an lvalue, decltype will return a reference to the data type of the expression
// If the expression is an rvalue, decltype will return the data type of the value


void decltype_example() {
    std::cout << "decltype example" << std::endl;

    int i = 1998; // Rvalue
    decltype(i) i2 = 2011; // Same as int i2 = 2011

    decltype((i)) iRef = i2; // (i) is an lvalue, reference returned
    std::cout << "iRef: " << iRef << std::endl;
    std::cout << "i2: " << i2 << std::endl;

    std::cout << std::endl;

    iRef = 2012;
    std::cout << "iRef: " << iRef << std::endl;
    std::cout << "i2: " << i2 << std::endl; // iRef is a reference after all

    // In line 81, the parentheses around i indicate that this is an expression instead of a variable.
    // Hence, decltype computes int& instead of int.

    // decltype is not used as often as auto.
    // It is useful with templates that can deduce the type of a function.
}

int func(int, int) {
    return 0; 
}


void decltype_example_two() {
    decltype(5) i = 5;                            // int

    int& intRef = i;	                             // int&
    decltype(intRef) intRefD = intRef;            // int&

    int* intPoint = &i;                           // int*
    decltype(intPoint) intPointD = intPoint;      // int*

    const int constInt = i;                       // const int
    decltype(constInt) constIntD = constInt;      // const int

    static int  staticInt = 10;                   // static int
    decltype(staticInt) staticIntD = staticInt;   // static int

    const std::vector<int> myVec;
    decltype(myVec) vecD = myVec;                 // const std::vector<int>

    auto myFunc = func;                           // (int)(*)(int, int)
    decltype(myFunc) myFuncD = myFunc;            // (int)(*)(int, int)

    // define a function pointer
    int (*myAdd1)(int, int) = [](int a, int b) { return a + b; };

    // use type inference of the C++11 compiler
    decltype(myAdd1) myAdd2 = [](int a, int b) { return a + b; };

    std::cout << "\n";

    // use the function pointer
    std::cout << "myAdd1(1, 2) = " << myAdd1(1, 2) << std::endl;

    // use the 2 variable
    std::cout << "myAdd2(1, 2) = " << myAdd2(1, 2) << std::endl;

    std::cout << "\n";
}

// Using auto and decltype together, a function template is able to automatically deduce its return type.
// Here’s a function with a trailing return type
template <typename T1, typename T2>
auto add(T1 first, T2 second) -> decltype(first + second)
{
    return first + second;
}

//The syntax above follows a few rules

// - auto : introduces the syntax for the delayed return type.
// - decltype : declares the return type.
// - The alternative function syntax is obligatory.
// - Using this strategy, the return type of the function can be deduced from the types of its arguments.

// C++14 makes things even simpler. We don’t need to use decltype to deduce the function’s return type anymore. 
// auto handles everything

template <typename T1, typename T2>
auto add_cpp_14(T1 first, T2 second) {
    return first + second;
}

// In the expression decltype(auto), auto uses the same rules to determine the type as decltype. 
// This means in particular, no decay takes place.
// Both declarations are identical

// - decltype(expr) v = expr;
// - decltype(auto) v = expr;

// This syntax also applies to the automatic return type of a function template
template <typename T1, typename T2>
decltype(auto) add_v3(T1 first, T2 second) {
    return first + second;
}


// ============================ exercises ============================

template<typename T1, typename T2>
auto add_v4(T1 first, T2 second) -> decltype(first + second) {
    return first + second;
}

void automatic_type_deduction_exercise_one() {
    std::cout << "automatic type deduction exercise one" << std::endl;
    // Let’s get used to the rules of implicit type casts by arithmetic operations.
    // Call the add function that we studied earlier with different arguments and ask for the return type of each operation with typeid.
    // Here are a few examples
    
    //std::cout << typeid( add(1, false) ).name() << std::endl; 
    std::cout << typeid(add_v4('a', 1)).name() << std::endl;
    std::cout << typeid(add_v4(false, false)).name() << std::endl;
    std::cout << typeid(add_v4(true, 3.14)).name() << std::endl;
    std::cout << typeid(add_v4(1, 4.0)).name() << std::endl;

}