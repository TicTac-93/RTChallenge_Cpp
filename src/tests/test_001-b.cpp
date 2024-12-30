/**
 * @file test_001-b.cpp
 * @brief Unit test for rt_datatypes.cpp
 *        Matrix classes and interoperability
 * @date 241230
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
	cout << "\nUNIT TEST - rt::M4x4 | rt::M3x3 | rt::M2x2" << endl;

	tests ++;
	test_name = "rt::M4x4 equality operators";
	rt::M4x4 d = rt::M4x4();
	rt::M4x4 d2 = rt::M4x4();
	d2.data[0][0] = 1;
	d2.data[1][1] = 1;
	d2.data[2][2] = 1;
	d2.data[3][3] = 1;
	if (d == rt::M4x4() 
			&& d != d2) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::M4x4 initializers";
	rt::M4x4 d3 = rt::M4x4();
	d3.init_identity();
	float cells_4x4a[4][4] = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	};
	float cells_4x4b[4][4] = {
		{-62.49,	37.85,	-1.86,	82.44},
		{-15.82,	-47.48,	45.84,	18.68},
		{14.01,		-32.78,	-50.00,	27.95},
		{-12.96,	56.62,	17.05,	-48.98}
	};
	d2 = rt::M4x4(cells_4x4a);
	rt::M4x4 d4 = rt::M4x4(cells_4x4b);
	if (d2 == d3
			&& d4 == rt::M4x4(cells_4x4b)
			&& d2 != d4) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::M4x4 mul operators";
	rt::M4x4 d5, d6, d7;
	float cells_4x4c[4][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2}
	};
	float cells_4x4d[4][4] = {
		{-2,  1,  2,  3},
		{ 3,  2,  1, -1},
		{ 4,  3,  6,  5},
		{ 1,  2,  7,  8}
	};
	float cells_4x4e[4][4] = {
		{20,  22,  50,  48},
		{44,  54, 114, 108},
		{40,  58, 110, 102},
		{16,  26,  46,  42}
	};
	d5 = rt::M4x4(cells_4x4c);
	d6 = rt::M4x4(cells_4x4d);
	d7 = rt::M4x4(cells_4x4e);
	if (d5.mul(d6) == d7
			&& (d5 * d6) == d7
			&& (d5 *= d6) == d7
			&& d5 == d7 ) {
				PASS();
			} else {
				FAIL(test_name);
	}



	tests ++;
	test_name = "rt::M3x3 equality operators";
	rt::M3x3 e = rt::M3x3();
	rt::M3x3 e2 = rt::M3x3();
	e2.data[0][0] = 1;
	e2.data[1][1] = 1;
	e2.data[2][2] = 1;
	if (e == rt::M3x3() 
			&& e != e2) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::M3x3 initializers";
	rt::M3x3 e3 = rt::M3x3();
	float cells_3x3a[3][3] = {
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1}
	};
	float cells_3x3b[3][3] = {
		{-62.49,	37.85,	-1.86},
		{-15.82,	-47.48,	45.84},
		{14.01,		-32.78,	-50.00}
	};
	e3 = rt::M3x3(cells_3x3a);
	rt::M3x3 e4 = rt::M3x3(cells_3x3b);
	if (e2 == e3
			&& e4 == rt::M3x3(cells_3x3b)
			&& e2 != e4) {
				PASS();
			} else {
				FAIL(test_name);
	}



	tests ++;
	test_name = "rt::M2x2 equality operators";
	rt::M2x2 f = rt::M2x2();
	rt::M2x2 f2 = rt::M2x2();
	f2.data[0][0] = 1;
	f2.data[1][1] = 1;
	if (f == rt::M2x2() 
			&& f != f2) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::M2x2 initializers";
	rt::M2x2 f3 = rt::M2x2();
	float cells_2x2a[2][2] = {
		{1, 0},
		{0, 1}
	};
	float cells_2x2b[2][2] = {
		{-62.49,	37.85},
		{-15.82,	-47.48}
	};
	f3 = rt::M2x2(cells_2x2a);
	rt::M2x2 f4 = rt::M2x2(cells_2x2b);
	if (f2 == f3
			&& f4 == rt::M2x2(cells_2x2b)
			&& f2 != f4) {
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