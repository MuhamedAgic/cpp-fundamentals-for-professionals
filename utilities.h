
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <utility>
#include <tuple>


void std_bind_std_function_exercise() {

    std::cout << std::endl;

    std::vector<int> myVec(20);
    std::iota(myVec.begin(), myVec.end(), 0);

    std::cout << "myVec: ";
    for (auto i : myVec) std::cout << i << " ";
    std::cout << std::endl;

    //std::function< bool(int)> myBindPred = std::bind(std::logical_and<bool>(),
    //    std::bind(std::greater <int>(), std::placeholders::_1, 9), std::bind(std::less <int>(), std::placeholders::_1, 16));

    //myVec.erase(std::remove_if(myVec.begin(), myVec.end(), myBindPred), myVec.end());

    //std::cout << "myVec: ";
    //for (auto i : myVec) std::cout << i << " ";

    // EXERCISE: Write your code here for Lambda function
    std::function<bool(int)> myLambdaPred = [](int x) {
        if (x > 9 && x < 16) {
            return true;
        }
        return false;
    };

    // THEIR SOLUTION
    //auto myLambdaPred = [](int a) {return (a > 9) && (a < 16); };


    myVec.erase(std::remove_if(myVec.begin(), myVec.end(), myLambdaPred), myVec.end());

    std::cout << "myVec: ";
    for (auto i : myVec) std::cout << i << " ";

    std::cout << std::endl;

}

// exercise

// Implement the python function divmod.

// The function divmod should return the result for the division of the numbers: 
// the integer part and the rest.

// From the documentation:
// divmod(x, y) ->(div, mod)

// Implement divmod function here

std::pair<int, int> div_mod(int x, int y) {
    int div = 0;
    int mod = x;

    for (int i = 0; i < static_cast<int>(x / y); i++) {
        if ((mod - y) > 0) {
            ++div;
            mod -= y;
        }
    }

    return std::pair(div, mod);
    //return std::pair<int, int>(div, mod); // int their version, type must be specified in order to run
}


// Their solution
std::tuple<int, int> divmod(int a, int b) {
    return std::make_tuple(a / b, a % b);
}


void test_div_mod_exercise() {

    // call your function here
    auto my_div_mod = div_mod(99, 10);

    std::cout << "Result div mod - div: " << my_div_mod.first << ", mod: " << my_div_mod.second << std::endl;

    // their solution
    auto res = divmod(10, 3);
    std::cout << "divmod(10, 3): " << "divmod(" << std::get<0>(res) << ", " << std::get<1>(res) << ")" << std::endl;

    std::cout << std::endl;
}
