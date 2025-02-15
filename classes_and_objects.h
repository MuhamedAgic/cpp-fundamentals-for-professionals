// copy constructors
// move constructors : They expect a non-constant rvalue-reference to an instance of the class as their argument.


#include <string>
#include <iostream>

class AnAccount {
public:
    AnAccount(Account&& other);
    // After the move operation, other is in a moved-from state. 
    // Accessing it will result in undefined behavior. 
    // To use it again, we would have to re-initialize it.

public:
    //explicit Account(double b) : balance(b) {} // Account a = 100.0; won't work
    AnAccount(double b) : balance(b) {}
private:
    double balance;
    std::string cur;
};

void implicit_contructor_example() {
    // we can do this if constructor is not explicit
    AnAccount a = 100.0;
}


class Widget {
public:

    // write simplified version of constructor here

    Widget() : width(640), height(480), frame(false), visible(true) {}

    Widget(int w) : width(w), height(getHeight(w)), frame(false), visible(true) {}

    Widget(int w, int h) : width(w), height(h), frame(false), visible(true) {}

    void show() {
        std::cout << std::boolalpha << width << "x" << height
            << ", frame: " << frame << ", visible: " << visible
            << std::endl;
    }
private:
    int getHeight(int w) { return w * 3 / 4; }
    int width;
    int height;
    bool frame;
    bool visible;
};

class WidgetImproved {
public:

    // write simplified version of constructor here

    WidgetImproved() {}
    WidgetImproved(int w) : width(w), height(getHeight(w)) {}
    WidgetImproved(int w, int h) : width(w), height(h) {}

    void show() {
        std::cout << std::boolalpha << width << "x" << height
            << ", frame: " << frame << ", visible: " << visible
            << std::endl;
    }
private:
    int getHeight(int w) { return w * 3 / 4; }
    int width = 640;
    int height = 480;
    bool frame = false;
    bool visible = true;
};



// exercise one: Simplify the constructors of the Widget class in the code below.Initialize the class members.
void initializer_for_instances_exercise_one() {
    std::cout << std::endl;

    Widget wVGA;
    Widget wSVGA(800);
    Widget wHD(1280, 720);

    Widget wVGAImproved;
    Widget wSVGAImproved(800);
    Widget wHDImproved(1280, 720);

    wVGA.show();
    wSVGA.show();
    wHD.show();

    wVGAImproved.show();
    wSVGAImproved.show();
    wHDImproved.show();

    std::cout << std::endl;
}


// constructor delegation

// Constructor delegation occurs when a constructor calls another constructor of the same class in its initializer list.


class MyHour {
    // In this example, the constructor in line 6 is responsible for creating a myHour object, whereas the other constructors simply call it in their initializer lists.
    // The constructors in lines 12 and 14 do not require a code in their body since they are simply creating a myHour object with the specified integer value.
    // For this, all they need to do is delegate the task to the first constructor.
public:
    MyHour(int hour) {
        if (0 <= hour && hour <= 23) myHour = hour;
        else myHour = 0;
        std::cout << "myHour = " << myHour << std::endl;
    }

    MyHour() : MyHour(0) {}

    MyHour(double hour) :MyHour(static_cast<int>(ceil(hour))) {}

private:
    int myHour;
};

void constructor_delegation_example() {

    std::cout << std::endl;

    MyHour(10);
    MyHour(100);
    MyHour();
    MyHour(22.45);

    std::cout << std::endl;

}


struct RecursiveConstructors {
    RecursiveConstructors(int) {}               // 1: non-delegating constructor
    RecursiveConstructors() : RecursiveConstructors(42) {}             // 2: delegates to 1
    //RecursiveConstructors(char c) : RecursiveConstructors(42.0) {}  // 3: ill-formed due to recursion with 4
    //RecursiveConstructors(double d) : RecursiveConstructors('a') {} // 4: ill-formed due to recursion with 3
};


// destructors
// A base class destructor should be either public and virtual or protected and nonvirtual. 
// This is quite easy to get. 
// If the destructor of the base class is protected, we cannot destroy derived objects using a base class pointer; 
// therefore, the destructor must not be virtual.

// classes
// if a class member is defined inside the class
// the compiler automatically considers it an inline function.

// Note: Static methods do not have this pointers. They can only access static attributes and methods.


// const methods
// Constant objects can only call const or constexpr methods.
// Constant methods can only change an instance variable if the instance variable is declared mutable.


// constexpr method rules
// It can also be evaluated at runtime if non - constexpr arguments are provided.
// One thing to remember is that constexpr methods are implicitly const.
// Such methods can only call other constexpr functions, methods, and global variables.
// constexpr methods can only be called by constexpr objects.


// this is an example where we specify that
// only doubles are accepted!
void onlyDouble(double) {}
template <typename T>
void onlyDouble(T) = delete;

// exercise one: Define a class template that can be invoked with an int value.
// e.g.
// OnlyInt(5); // ok
// OnlyInt(5L); // ERROR

void OnlyInt(int a) {
    std::cout << "only int: " << a << std::endl;
}

template <typename T>
void OnlyInt(T someType) = delete;


void delete_exercise_one() {
    OnlyInt(999);
    //OnlyInt(999L);
}


// operator overloading:

// To achieve perfect operator overloading, there is a large set of rules we have to follow. Here are some of the important ones.

//We cannot change the precedence of an operator. The compiler computes all operators in order of precedence.We cannot alter this order.Hence, whatever operation our operator performs, it will be computed after the operator with higher precedence.
//Derived classes inherit all the operators of their base classes except the assignment operator. Each class needs to overload the = operator.
//All operators other than the function call operator cannot have default arguments.
//Operators can be called explicitly.A benefit of overloading an operator is that it can be used directly with its operands.However, the compiler may cause some implicit conversion in this process.We can make explicit calls to the overloaded operator in the following format : a.operator += (b).


// explicit conversions

// exercise one: Adjust the following program so that all implicit conversions are possible. 
// Does the program behave as expected?

// removing explicit keywords made it compile and run

class A {};

class B {};

class MyClassExplicit {
public:
    MyClassExplicit() {}
    MyClassExplicit(A) {}                // since C++98
    operator B() { return B(); }   // new with C++11
};

void needMyClass(MyClassExplicit) {};
void needB(B) {};

struct MyBool {
    operator bool() { return true; }
};

void explicit_conversion_exercise_one() {

    // A -> MyClass
    A a;

    // explicit invocation
    MyClassExplicit myClass1(a);
    // implicit conversion from A to MyClass
    MyClassExplicit myClass2 = a;
    needMyClass(a);

    // MyClass -> B
    MyClassExplicit myCl;

    // explicit invocation
    B b1(myCl);
    // implicit conversion from MyClass to B
    B b2 = myCl;
    needB(myCl);

    // MyBool -> bool conversion
    MyBool myBool;
    if (myBool) {};
    int myNumber = (myBool) ? 1998 : 2011;
    // implict conversion
    int myNewNumber = myBool + myNumber;
    auto myTen = (20 * myBool - 10 * myBool) / myBool;

    std::cout << myTen << std::endl;
}




// call operator

// A functor that takes a single argument is a unary functor.
// A functor that takes two arguments is a binary functor.


// Note: Lambda functions can also have a state.


class SumMe {
public:

    SumMe() : sum(0) {};

    void operator()(int x) {
        sum += x;
    }

    int getSum() const {
        return sum;
    }
private:
    int sum;
};

void func_obj_example() {

    // The std::for_each call is a special algorithm of the Standard Template Library.
    // It can return its callable.
    // We invoke std::for_each with the function object SumMe and can, therefore, store the result of the function call directly in the function object.
    // we used the sum of all calls which is the state of the function object.

    std::cout << std::endl;

    std::vector<int> intVec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    SumMe sumMe = std::for_each(intVec.begin(), intVec.end(), SumMe());
    std::cout << "sumMe.getSum(): " << sumMe.getSum() << std::endl;

    std::cout << std::endl;

}

// exercise one: Implement the functionality in the example we saw in the previous lesson with the help of a lambda function.

void call_operator_exercise_one() {
    std::cout << std::endl;

    std::vector<int> intVec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    //int result = 0;
    //int sumMe = std::for_each(
    //    intVec.begin(), 
    //    intVec.end(),
    //    [&result](int x) -> int {
    //        return result + x;
    //    }
    //);

    // from solution
    int result = 0;
    std::for_each(
        intVec.begin(), 
        intVec.end(),
        [&result](int x) {
            result += x;
        }
    );
    std::cout << "sumMe result: " << result << std::endl;

    std::cout << std::endl;
}

// friends
// A class can declare friendship to a function, a method, or a class.

// Rules:
// The declaration of a friendship can be anywhere.
// The access specifier of the friendship declaration is not relevant.
// Friendship cannot be inherited(your friend’s children are not your friends).
// Friendship is not transitive(a friend of your friend is not your friend).

// Access specifiers have no effect on the meaning of friend declarations (they can appear in private: or in public: sections, with no differences).
// A friend has full control of the internals of a class.


// union
// A union is a special data type where all members start at the same address. 
// A union can only hold one type at a time, therefore, we can save memory. 
// A tagged union is a union that keeps track of its types. 
// By using union, we are actually pointing to the same memory for the different data types used.


// Rules 
// Unions are special class types.

// Only one member can exist at any one point in time.
// They only need as much space as the biggest member requires, which saves memory.
// The access specifier is public by default.
// They cannot have virtual methods like with Inheritance.
// They cannot have references.
// They cannot be inherited nor inherited from.


union Value {
    int i;
    double d;
};

void union_example() {
    Value v = { 123 };      // now v holds an int
    std::cout << v.i << '\n';    // write 123
    v.d = 987.654;          // now v holds a double
    std::cout << v.d << '\n';    // write 987.654
}


