/**
 * @file test_001-a.cpp
 * @brief Unit test for rt::Point and rt::Vec3 data types
 * @date 241126
 */

#include <iostream>
#include "../lib/rt_datatypes.hpp"
#include "../lib/rt_utils.hpp"
using namespace std;
using namespace rtutil;

int main() {
    bool all_passed = true;
    int tests = 0;
    int passed = 0;

    cout << "UNIT TEST - rt::Point | rt::Vec3 | rt::Float4\n" << endl;

    tests ++;
    cout << "rt::Point a(4.3, -4.2, 3.1)";
    rt::Point a = rt::Point(4.3, -4.2, 3.1);
    cout << "\na.x = " << a.x;
    cout << "\na.y = " << a.y;
    cout << "\na.z = " << a.z;
    rt::Float4 af4 = a.float4();
    cout << "\na.float4() = (" << af4.w << ", " << af4.x << ", " << af4.y << ", " << af4.z << ")" << endl;

    if (a.x == 4.3f &&
        a.y == -4.2f &&
        a.z == 3.1f &&
        af4.w == 1.0f) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    tests ++;
    cout << "rt::Vec3 b(-1.2, 5.3, -3.1)";
    rt::Vec3 b = rt::Vec3(-1.2, 5.3, -3.1);
    cout << "\nb.x = " << b.x;
    cout << "\nb.y = " << b.y;
    cout << "\nb.z = " << b.z;
    rt::Float4 bf4 = b.float4();
    cout << "\nb.float4() = (" << bf4.w << ", " << bf4.x << ", " << bf4.y << ", " << bf4.z << ")" << endl;

    if (is_equal(b.x, -1.2f) &&
        is_equal(b.y, 5.3f) &&
        is_equal(b.z, -3.1f) &&
        is_equal(bf4.w, 0.0f)) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    tests ++;
    cout << "rt::Point a2 = a.move(b)";
    rt::Point a2 = a.move(b);
    cout << "\na2.x = " << a2.x;
    cout << "\na2.y = " << a2.y;
    cout << "\na2.z = " << a2.z;

    if (is_equal(a2.x, 3.1f) &&
        is_equal(a2.y, 1.1f) &&
        is_equal(a2.z, 0.0f)) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    tests ++;
    cout << "rt::Vec3 b2 = a2.vec(a)";
    rt::Vec3 b2 = a2.vec(a);
    cout << "\nb2.x = " << b2.x;
    cout << "\nb2.y = " << b2.y;
    cout << "\nb2.z = " << b2.z;

    if (is_equal(b2.x, 1.2f) &&
        is_equal(b2.y, -5.3f) &&
        is_equal( b2.z, 3.1f)) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    tests ++;
    cout << "rt::Point() and == check";
    rt::Point a3 = rt::Point();
    a3.x = 4.3;
    a3.y = -4.2;
    a3.z = 3.1;
    
    if (a == a3 &&
        a != a2) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    tests ++;
    cout << "rt::Vec3 sub mult div";
    cout << "\nb3 = b.sub(Vec3(1,1,1))";
    rt::Vec3 b3 = b.sub(rt::Vec3(1,1,1));
    cout << "\nb4 = b.mult(3)";
    rt::Vec3 b4 = b.mult(3);
    cout << "\nb5 = b.div(3)";
    rt::Vec3 b5 = b.div(3);
    cout << "\nb3.x = " << b3.x;
    cout << "\nb3.y = " << b3.y;
    cout << "\nb3.z = " << b3.z;
    cout << "\nb4.x = " << b4.x;
    cout << "\nb4.y = " << b4.y;
    cout << "\nb4.z = " << b4.z;
    cout << "\nb5.x = " << b5.x;
    cout << "\nb5.y = " << b5.y;
    cout << "\nb5.z = " << b5.z;
    
    if (is_equal(b3.x, -2.2f) &&
        is_equal(b3.y, 4.3f) &&
        is_equal(b3.z, -4.1f) &&
        is_equal(b4.x, -3.6f) &&
        is_equal(b4.y, 15.9f) &&
        is_equal(b4.z, -9.3f) &&
        is_equal(b5.x, (-1.2f / 3)) &&
        is_equal(b5.y, (5.3f / 3)) &&
        is_equal(b5.z, (-3.1f / 3))) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    tests ++;
    cout << "rt::Vec3 mag normalize";
    cout << "\nrt::Vec3 b6 = Vec3(2, 0, 0)";
    rt::Vec3 b6 = rt::Vec3(2, 0, 0);
    cout << "\nb6m = b6.mag()";
    float b6m = b6.mag();
    cout << "\nb6n = b6.normalize()";
    rt::Vec3 b6n = b6.normalize();
    cout << "\nb6m = " << b6m;
    cout << "\nb6n.x = " << b6n.x;
    cout << "\nb6n.y = " << b6n.y;
    cout << "\nb6n.z = " << b6n.z;
    
    if (is_equal(b6m, 2.0f) &&
        is_equal(b6n.x, 1.0f) &&
        is_equal(b6n.y, 0.0f) &&
        is_equal(b6n.z, 0.0f)) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    tests ++;
    cout << "rt::Vec3 equality operator";    
    if (rt::Vec3(-1.2, 5.3, -3.1) == b &&
        rt::Vec3(-1.2, 5.3, -3.1) != b2) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }
        
    tests ++;
    cout << "rt::Vec3 add / sub operators";
    cout << "\nrt::Vec3 b7(1, 2, 3)";
    rt::Vec3 b7 = rt::Vec3(1, 2, 3);
    cout << "\nb + b7: (" << (b + b7).x << ", " << (b + b7).y << ", " << (b + b7).z << ")";
    cout << "\nb - b7: (" << (b - b7).x << ", " << (b - b7).y << ", " << (b - b7).z << ")";
    b7 += b7;
    cout << "\nb7 += b7: (" << b7.x << ", " << b7.y << ", " << b7.z << ")";
    b7 -= b;
    cout << "\nb7 -= b: (" << b7.x << ", " << b7.y << ", " << b7.z << ")";
    cout << "\n-b7: (" << -b7.x << ", " << -b7.y << ", " << -b7.z << ")";

    b7 = rt::Vec3(1, 2, 3);
    if (rt::Vec3(-0.2, 7.3, -0.1) == (b + b7) &&
        rt::Vec3(-2.2, 3.3, -6.1) == (b - b7) &&
        rt::Vec3(2, 4, 6) == (b7 += b7) &&
        rt::Vec3(3.2, -1.3, 9.1) == (b7 -= b) &&
        rt::Vec3(-3.2, 1.3, -9.1) == -b7) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    cout << "===================="
         << "\n    Passed " << passed << "/" << tests
         << "\n   All Passed: " << all_passed
         << "\n====================" << endl;
    
}