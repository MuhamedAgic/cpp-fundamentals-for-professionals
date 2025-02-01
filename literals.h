// There are 2 types of literals, raw and cooked

// Exercise 1: extend the MyDistance so it supports the following:
//  Feet: 1 ft = 0.3048m
//  Mile : 1 mi = 1609.344m

// Exercise 2: Extend MyDistance so that we can calculate the total distance based on the following formula:
// myDistPerWeek = 4 * work * 2 - 3 * abbreviationToWork + workout + shopping
// work is in km whereas all the others are in m. 
// All of them are long doubles.


#include <iostream>
#include <ostream>

namespace Distance {
    class MyDistance {
    public:
        MyDistance(double i) :m(i) {}

        friend MyDistance operator +(const MyDistance& a, const MyDistance& b) {
            return MyDistance(a.m + b.m);
        }
        friend MyDistance operator -(const MyDistance& a, const MyDistance& b) {
            return MyDistance(a.m - b.m);
        }
        friend MyDistance operator *(const MyDistance& a, const MyDistance& b) {
            return MyDistance(a.m * b.m);
        }

        friend std::ostream& operator<< (std::ostream& out, const MyDistance& myDist) {
            out << myDist.m << " m";
            return out;
        }
    private:
        double m;

    };

    namespace Unit {
        MyDistance operator "" _km(long double d) {
            return MyDistance(1000 * d);
        }
        MyDistance operator "" _m(long double m) {
            return MyDistance(m);
        }
        MyDistance operator "" _dm(long double d) {
            return MyDistance(d / 10);
        }
        MyDistance operator "" _cm(long double c) {
            return MyDistance(c / 100);
        }
        MyDistance operator "" _feet(long double f) {
            return MyDistance(f * 0.3048);
        }
        MyDistance operator "" _mile(long double m) {
            return MyDistance(m * 1609.344);
        }

    }
}


void literals_exercise() {
    using namespace Distance::Unit;

    std::cout << std::endl;

    std::cout << "1.0_km: " << 1.0_km << std::endl;
    std::cout << "1.0_m: " << 1.0_m << std::endl;
    std::cout << "1.0_dm: " << 1.0_dm << std::endl;
    std::cout << "1.0_cm: " << 1.0_cm << std::endl;
    std::cout << "1.0_feet: " << 1.0_feet << std::endl;
    std::cout << "1.0_mile: " << 1.0_mile << std::endl;

    Distance::MyDistance myDistPerWeek = 0.0_m;
    Distance::MyDistance work = 50.0_km;
    Distance::MyDistance workout = 10000.0_m; // 10 km
    Distance::MyDistance abbreviationToWork = 5.0_m;
    Distance::MyDistance shopping = 3000.0_m;

    myDistPerWeek = 4 * work * 2 - 3 * abbreviationToWork + workout + shopping;

    std::cout << "My distance per week: " << myDistPerWeek << std::endl;
    std::cout << std::endl;
    std::cout << "1.0_km + 2.0_dm +  3.0_dm - 4.0_cm: " << 1.0_km + 2.0_dm + 3.0_dm - 4.0_cm << std::endl;
    std::cout << std::endl;

}