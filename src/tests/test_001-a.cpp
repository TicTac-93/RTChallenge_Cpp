/**
 * @file test_001-a.cpp
 * @brief Unit test for rt_datatypes.cpp
 * 				Point, Vec3, Float4, and RGB classes
 * @date 241202
 */

#include <iostream>
#include "../lib/rt_datatypes.hpp"
#include "../lib/rt_utils.hpp"
using namespace std;
using namespace rtutil;

bool all_passed = true;
int tests = 0;
int passed = 0;
string test_name;
int failed = 0;
string fail_list[999];

void PASS () {
	// cout << "\n[PASS]\n" << endl;
	passed ++;
}

void FAIL (string name) {
	// cout << "\n[FAIL]\n" << endl;
	all_passed = false;
	fail_list[failed] = test_name;
	failed ++;
}

int main() {

	cout << "\nUNIT TEST - rt::Point | rt::Vec3 | rt::Float4 | rt::RGB" << endl;
	tests ++;
	test_name = "rt::Point a(4.3, -4.2, 3.1)";
	rt::Point a = rt::Point(4.3, -4.2, 3.1);
	rt::Float4 af4 = a.float4();
	if (a.x == 4.3f
			&& a.y == -4.2f
			&& a.z == 3.1f
			&& af4.w == 1.0f) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Vec3 b(-1.2, 5.3, -3.1)";
	rt::Vec3 b = rt::Vec3(-1.2, 5.3, -3.1);
	rt::Float4 bf4 = b.float4();

	if (is_equal(b.x, -1.2f)
			&& is_equal(b.y, 5.3f)
			&& is_equal(b.z, -3.1f)
			&& is_equal(bf4.w, 0.0f)) {
				PASS();
			} else {
				FAIL(test_name);
	}



	tests ++;
	test_name = "rt::Point a2 = a.move(b)";
	rt::Point a2 = a.move(b);

	if (is_equal(a2.x, 3.1f)
			&& is_equal(a2.y, 1.1f)
			&& is_equal(a2.z, 0.0f)) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Vec3 b2 = a2.vec_to(a)";
	rt::Vec3 b2 = a2.vec_to(a);

	if (is_equal(b2.x, 1.2f)
			&& is_equal(b2.y, -5.3f)
			&& is_equal( b2.z, 3.1f)) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Point() != and == check";
	rt::Point a3 = rt::Point();
	a3.x = 4.3;
	a3.y = -4.2;
	a3.z = 3.1;
	
	if (a == a3
			&& a != a2) {
				PASS();
			} else {
				FAIL(test_name);
	}



	tests ++;
	test_name = "rt::Vec3 equality operator";
	if (rt::Vec3(-1.2, 5.3, -3.1) == b
			&& rt::Vec3(-1.2, 5.3, -3.1) != b2) {
				PASS();
			} else {
				FAIL(test_name);
	}
		
	tests ++;
	test_name = "rt::Vec3 add / sub operators";
	rt::Vec3 b7 = rt::Vec3(1, 2, 3);
	if (rt::Vec3(-0.2, 7.3, -0.1) == (b + b7)
			&& rt::Vec3(-2.2, 3.3, -6.1) == (b - b7)
			&& rt::Vec3(2, 4, 6) == (b7 += b7)
			&& rt::Vec3(3.2, -1.3, 9.1) == (b7 -= b)
			&& rt::Vec3(-3.2, 1.3, -9.1) == -b7) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Vec3 mul div";
	rt::Vec3 b3 = rt::Vec3(1, 2, 3);
	rt::Vec3 b4 = b3.mul(2.5);
	rt::Vec3 b5 = b3.div(2);
	
	if (b4 == rt::Vec3(2.5, 5, 7.5)
			&& b5 == rt::Vec3(0.5, 1, 1.5)) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Vec3 mag normalize";
	rt::Vec3 b6 = rt::Vec3(2, 0, 0);
	float b6m = b6.mag();
	rt::Vec3 b6n = b6.normalize();
	
	if (is_equal(b6m, 2.0f)
			&& is_equal(b6n.x, 1.0f)
			&& is_equal(b6n.y, 0.0f)
			&& is_equal(b6n.z, 0.0f)) {
				PASS();
			} else {
				FAIL(test_name);
	}



	tests ++;
	test_name = "rt::RGB constructors";
	rt::RGB c = rt::RGB(.1, .2, .3);
	rt::RGB c2 = rt::RGB();
	if (is_equal(c.r, .1)
			&& is_equal(c.g, .2)
			&& is_equal(c.b, .3)
			&& is_equal(c2.r, 0)
			&& is_equal(c2.g, 0)
			&& is_equal(c2.b, 0)) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::RGB equality operator";
	if (rt::RGB(.1, .2, .3) == c
			&& rt::RGB(.2, -1, 3.1) != c) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::RGB mul";
	rt::RGB c3 = c.mul(2);
	if (c3 == rt::RGB(.2, .4, .6)) {
		PASS();
	} else {
		FAIL(test_name);
	}

	tests ++;
	test_name = "rt::RGB add / sub operators";
	if (rt::RGB(.3, .6, .9) == (c + c3)
			&& rt::RGB(-.1, -.2, -.3) == (c - c3)
			&& rt::RGB(.3, .6, .9) == (c += c3)
			&& rt::RGB(-.1, -.2, -.3) == (c3 -= c)
			&& rt::RGB(-.3, -.6, -.9) == -c) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::RGB mul operators";
	if (rt::RGB(-.03, -.12, -.27) == (c * c3)
			&& rt::RGB(.09, .36, .81) == (c *= c)) {
				PASS();
			} else {
				FAIL(test_name);
	}



	cout << "===================="
			 << "\n    Passed " << passed << "/" << tests
			 << "\n====================" << endl;

	if (!all_passed) {
		for (int i=0; i<failed; i++) {
			cout << "\n" << fail_list[i] << " FAILED!";
		}
		cout << endl;
	}

	return all_passed;
	
}