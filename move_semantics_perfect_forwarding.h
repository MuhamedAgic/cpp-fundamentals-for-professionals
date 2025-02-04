//  The binding of rvalues to rvalue references has higher priority.

#include <algorithm>
#include <iostream>
#include <string>

// Move semantics
// Cheap moving of objects instead of expensive copying.
// No memory allocation and deallocation.
// Non - copyable but movable objects can be transferred by value.

// Perfect forwarding
// Forward an object without changing its rvalue / lvalue nature.
// This helps in function templates.

// example
struct MyDataLRVal {};

std::string function(const MyDataLRVal&) {
    return "lvalue reference";
}

std::string function(MyDataLRVal&&) {
    return "rvalue reference";
}

void lr_value_example() {

    std::cout << std::endl;

    MyDataLRVal myData;

    std::cout << "function(myData): " << function(myData) << std::endl;
    std::cout << "function(MyData()): " << function(MyDataLRVal()) << std::endl;
    std::cout << "function(std::move(myData)): " << function(std::move(myData)) << std::endl;

    std::cout << std::endl;

}

// With the copy semantic, it is possible that a std::bad_alloc will be thrown because our program is out of memory.
// The resource of the move operation is in a “valid but unspecified state” afterward.

void copy_example() {
    std::string str1("ABCDEF");
    std::string str2;
    str2 = str1;
    std::cout << "after copy - str1: " << str1 << ", str2: " << str2 << std::endl;
}

void move_example() {
    std::string str1("ABCDEF");
    std::string str2;
    str2 = std::move(str1);
    std::cout << "after move - str1: " << str1 << ", str2: " << str2 << std::endl;
}


// The string str1 is empty after the move operation. 
// This is not guaranteed, but is often the case. 
// We explicitly requested the move semantic with the function std::move. 
// The compiler will automatically perform the move semantic if it is sure that the source of the move semantic is not needed anymore.
// 
// We will explicitly request the move semantic in our program by using std::move.
// Although it is called std::move, we should have a different mental picture in mind.
// When we move an object, we transfer ownership.
// By moving, we give the object to someone else.

// A class supports copy semantics if the class has a copy constructor and a copy assignment operator.
// A class supports move semantics if the class has a move constructor and a move assignment operator.
// If a class has a copy constructor, it should also have a copy assignment operator. 
// The same holds true for the move constructor and move assignment operator.

template <typename T>
void swap_v1(T& a, T& b) {
    T tmp(a);
    a = b;
    b = tmp;
}

template <typename T>
void swap(T& a, T& b) {
    T tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

// The T tmp(a); command essentially:
// - allocates tmp and each element from tmp.
// - copies each element from a to tmp.
// - deallocates tmp and each element from tmp.

// The T tmp(std::move(a)); command:
// - Redirects the pointer from tmp to a.


// move semantics
//The function std::move moves its resource.

// Needs the header <utility>.
// Converts the type of its argument into a rvalue reference.
// The compiler applies the move semantic to the rvalue reference.
// Is a static_cast to a rvalue reference under the hood.

// static_cast<std::remove_reference<decltype(arg)>::type&&>(arg);

// What is happening here ?
// - decltype(arg) : deduces the type of the argument.
// - std::remove_reference<....> removes all references from the type of the argument.
// - static_cast<....> && adds two references to the type.

// Copy semantic is a fallback for move semantic. 
// This means if we invoke std::move with a non-moveable type, 
// copy-semantic is used because an rvalue can be bound to an rvalue reference and a constant lvalue reference.

// exercise one: 
// - In the program below, a BigArray with 10 billion entries will be pushed to a std::vector.
// - Compile the program and measure its performance.

using std::cout;
using std::endl;

using std::chrono::system_clock;
using std::chrono::duration;

using std::vector;

class BigArray {

public:
    BigArray(size_t len) : len_(len), data_(new int[len]) {}

    explicit BigArray(const BigArray& other) : len_(other.len_), data_(new int[other.len_]) {
        cout << "Copy construction of " << other.len_ << " elements " << endl;
        std::copy(other.data_, other.data_ + len_, data_);
    }

    // add move constructor
    BigArray(BigArray&& other) :
        len_(other.len_),
        data_(new int[other.len_]) {
        cout << "Move construction of " << other.len_ << " elements" << endl;
        other.data_ = nullptr;
        other.len_ = 0;
    }

    BigArray& operator = (const BigArray& other) {
        cout << "Copy assignment of " << other.len_ << " elements " << endl;
        if (this != &other) {
            delete[] data_;

            len_ = other.len_;
            data_ = new int[len_];
            std::copy(other.data_, other.data_ + len_, data_);
        }
        return *this;
    }

    // move assignment operator
    BigArray& operator = (BigArray&& other) {
        cout << "Move assignment of " << other.len_ << " elements" << endl;
        if (this != &other) {
            delete[] data_; // delete current data

            // assign data of other to *this
            this->data_ = other.data_;
            this->len_ = other.len_;

            // clean other data after elements have been moved
            other.data_ = nullptr;
            other.len_ = 0;
        }
        return *this;
    }

    ~BigArray() {
        if (data_ != nullptr) delete[] data_;
    }


private:
    size_t len_;
    int* data_;
};

void move_semantics_exercise_one() {
    // move in this example ~10x faster

    cout << endl;

    vector<BigArray> myVec;

    auto begin = system_clock::now();

    myVec.push_back(BigArray(1000000000));

    auto end = system_clock::now() - begin;
    auto timeInSeconds = duration<double>(end).count();

    cout << endl;
    cout << "time in seconds: " << timeInSeconds << endl;
    cout << endl;

}

// exercise 2: Extend BigArray with the move semantic and measure the performance once more. How big is the performance gain?

// Perfect forwarding
// Definition: If a function template forwards its arguments without changing their lvalue or rvalue characteristics, we call it perfect forwarding.

// A perfect factory method is a totally generic factory method. In particular, it implies that the function should have the following characteristics:
// - takes an arbitrary number of arguments.
// - accepts lvalues and rvalues as arguments.
// - forwards its arguments in the same way as the underlying constructor.


// example of perfect forwarding instead of overloading
// of different functions (lval ref, const lval ref, rval ref...)

template <typename T, typename Arg>
T create_perfect_forward(Arg&& a) {
    return T(std::forward<Arg>(a));
}

void perfect_forwarding_example() {

    std::cout << std::endl;

    // Lvalues
    int five = 5;
    int myFive = create_perfect_forward<int>(five);
    std::cout << "myFive: " << myFive << std::endl;

    // Rvalues
    int myFive2 = create_perfect_forward<int>(5);
    std::cout << "myFive2: " << myFive2 << std::endl;

    std::cout << std::endl;

}

// The (Arg&& a) universal reference in line 4 is a powerful reference that can bind lvalues or rvalues. 
// Sometimes the term perfect forwarding reference is used for this special reference.
// To achieve perfect forwarding, we have to combine a universal reference with std::forward.std::forward<Arg>(a) returns the underlying type of a, because a is a universal reference.
// We can think of std::forward as a conditional move operation.

// When the argument a is an rvalue, std::forward moves its argument. 
// When the argument a is an lvalue, it copies the argument. 
// Therefore, an rvalue remains an rvalue.

template<class T>
void wrapper(T&& a) {
    func(std::forward<T>(a));
}


// Variadic Templates are templates that can get an arbitrary number of arguments.
// That is exactly the feature missing from our current perfect factory method.

// Another example
// The three dots, are the so-called parameter pack. 
// If the three dots (also called ellipsis) are on the left of Args, the parameter pack will be packed; 
// if they are on the right of arg, the parameter pack will be unpacked.
template <typename T, typename ... Args>
T create_example(Args&& ... args) {
    return T(std::forward<Args>(args)...);
}

struct StructExample {
    StructExample(int i, double d, std::string s) {}
};

void perfect_forwarding_example_two() {

    std::cout << std::endl;

    // Lvalues
    int five = 5;
    int myFive = create_example<int>(five);
    std::cout << "myFive: " << myFive << std::endl;

    std::string str{ "Lvalue" };
    std::string str2 = create_example<std::string>(str);
    std::cout << "str2: " << str2 << std::endl;

    // Rvalues
    int myFive2 = create_example<int>(5);
    std::cout << "myFive2: " << myFive2 << std::endl;

    std::string str3 = create_example<std::string>(std::string("Rvalue"));
    std::cout << "str3: " << str3 << std::endl;

    std::string str4 = create_example<std::string>(std::move(str3));
    std::cout << "str4: " << str4 << std::endl;

    // Arbitrary number of arguments
    double doub = create_example<double>();
    std::cout << "doub: " << doub << std::endl;

    StructExample myStr = create_example<StructExample>(2011, 3.14, str4);

    std::cout << std::endl;

}


// perfect forwarding exercise one
// Use the perfect factory method in the code below and make a variadic template to use it with different types.

template <typename T, typename T1>
T create_before_exercise(T1&& t1) {
    return T(std::forward<T1>(t1));
}

template <typename T, typename ... Args>
T create(Args&& ... args) {
    return T(std::forward<Args>(args)...);
}

void perfect_forwarding_exercise_one() {
    std::cout << std::endl;

    // Lvalues
    int five = 5;
    int myFive = create<int>(five);
    std::cout << "myFive: " << myFive << std::endl;

    std::string str{ "Lvalue" };
    std::string str2 = create<std::string>(str);
    std::cout << "str2: " << str2 << std::endl;

    // Rvalues
    int myFive2 = create<int>(5);
    std::cout << "myFive2: " << myFive2 << std::endl;

    std::string str3 = create<std::string>(std::string("Rvalue"));
    std::cout << "str3: " << str3 << std::endl;

    std::string str4 = create<std::string>(std::move(str3));
    std::cout << "str4: " << str4 << std::endl;

    std::cout << std::endl;
}