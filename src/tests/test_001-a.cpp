/**
 * @file test_001-a.cpp
 * @brief Unit test for rt::Point and rt::Vec3 data types
 * @date 241126
 */

#include <iostream>
#include "../lib/rt_datatypes.hpp"
using namespace std;

int main() {
    cout << "UNIT TEST - rt::Point / rt::Vec3\n" << endl;

    cout << "rt::Point a(4.3, -4.2, 3.1)";
    rt::Point a = rt::Point(4.3, -4.2, 3.1);
    cout << "\na.x = " << a.x;
    cout << "\na.y = " << a.y;
    cout << "\na.z = " << a.z;
    cout << "\na.float4() = " << (string)a.float4();
    cout << "\na is a point (this isn't really a test, c++ is typed)" << endl;

    cout << "\nrt::Vec3 b(4.3, -4.2, 3.1)";
    rt::Vec3 b = rt::Vec3(4.3, -4.2, 3.1);
    cout << "\nb.x = " << b.x;
    cout << "\nb.y = " << b.y;
    cout << "\nb.z = " << b.z;
    cout << "\nb.float4() = " << (string)b.float4();
    cout << "\nb is a vector (this isn't really a test, c++ is typed)" << endl;

    // Since this is about validation as well as feedback, set up some logic tests to print a PASS / FAIL message
    // automatically.  They should mirror the terminal outputs above.
    
}