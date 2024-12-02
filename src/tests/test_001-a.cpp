/**
 * @file test_001-a.cpp
 * @brief Unit test for rt_datatypes.cpp
 * @date 241202
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

    cout << "UNIT TEST - rt::Point | rt::Vec3 | rt::Float4 | rt::RGB\n" << endl;

    tests ++;
    cout << "rt::Point a(4.3, -4.2, 3.1)";
    rt::Point a = rt::Point(4.3, -4.2, 3.1);
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
    cout << "rt::Vec3 b2 = a2.vec_to(a)";
    rt::Vec3 b2 = a2.vec_to(a);

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
    cout << "rt::Point() != and == check";
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

    tests ++;
    cout << "rt::Vec3 mul div";
    cout << "\nb3 = Vec3(1, 2, 3)";
    rt::Vec3 b3 = rt::Vec3(1, 2, 3);
    cout << "\nb4 = b3.mul(2)";
    rt::Vec3 b4 = b3.mul(2.5);
    cout << "\nb5 = b3.div(2)";
    rt::Vec3 b5 = b3.div(2);
    
    if (b4 == rt::Vec3(2.5, 5, 7.5) &&
        b5 == rt::Vec3(0.5, 1, 1.5)) {
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
    cout << "rt::RGB constructors";
    rt::RGB c = rt::RGB(.1, .2, .3);
    rt::RGB c2 = rt::RGB();
    if (is_equal(c.r, .1) &&
        is_equal(c.g, .2) &&
        is_equal(c.b, .3) &&
        is_equal(c2.r, 0) &&
        is_equal(c2.g, 0) &&
        is_equal(c2.b, 0)) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    tests ++;
    cout << "rt::RGB equality operator";
    rt::RGB c = rt::RGB(.1, .2, .3);
    if (rt::RGB(.1, .2, .3) == c &&
        rt::RGB(.2, -1, 3.1) != c) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    tests ++;
    cout << "rt::RGB mul";
    rt::RGB c3 = c.mul(2);
    cout << "RGB c3 = c.mul(2)";
    if (c3 == rt::RGB(.2, .4, .6)) {
            cout << "\n[PASS]\n" << endl;
            passed ++;
        } else {
            cout << "\n[FAIL]\n" << endl;
            all_passed = false;
        }

    // TODO: Add tests for RGB operators

    cout << "===================="
         << "\n    Passed " << passed << "/" << tests
         << "\n   All Passed: " << all_passed
         << "\n====================" << endl;

    return all_passed;
    
}