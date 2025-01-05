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
bool exc_test = true;
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

	// tests ++;
	// test_name = "rt::M4x4 mul operators";
	// rt::M4x4 d5, d6, d7;
	// float cells_4x4c[4][4] = {
	// 	{1, 2, 3, 4},
	// 	{5, 6, 7, 8},
	// 	{9, 8, 7, 6},
	// 	{5, 4, 3, 2}
	// };
	// float cells_4x4d[4][4] = {
	// 	{-2,  1,  2,  3},
	// 	{ 3,  2,  1, -1},
	// 	{ 4,  3,  6,  5},
	// 	{ 1,  2,  7,  8}
	// };
	// float cells_4x4e[4][4] = {
	// 	{20,  22,  50,  48},
	// 	{44,  54, 114, 108},
	// 	{40,  58, 110, 102},
	// 	{16,  26,  46,  42}
	// };
	// d5 = rt::M4x4(cells_4x4c);
	// d6 = rt::M4x4(cells_4x4d);
	// d7 = rt::M4x4(cells_4x4e);
	// if (d5.mul(d6) == d7
	// 		&& (d5 * d6) == d7
	// 		&& (d5 *= d6) == d7
	// 		&& d5 == d7 ) {
	// 			PASS();
	// 		} else {
	// 			FAIL(test_name);
	// }

	// tests ++;
	// test_name = "rt::M4x4 Point / Vec3 multiplication";
	// rt::Point p1 = rt::Point(1, 2, 3);
	// rt::Vec3 v1 = rt::Vec3(4, 5, 6);
	// rt::M4x4 d8;
	// float cells_4x4f[4][4] = {
	// 	{1, 2, 3, 4},
	// 	{2, 4, 4, 2},
	// 	{8, 6, 4, 1},
	// 	{0, 0, 0, 1}
	// };
	// d8 = rt::M4x4(cells_4x4f);
	// if (d8.mul(p1) == rt::Point(18, 24, 33)
	// 		&& d8.mul(v1) == rt::Vec3(32, 52, 86)
	// 		&& d3.mul(p1) == p1		// d3 is a 4x4 IDENTITY matrix
	// 		&& d3.mul(v1) == v1) {
	// 			PASS();
	// 		} else {
	// 			FAIL(test_name);
	// }

	// tests ++;
	// test_name = "rt::M4x4 transpose";
	// rt::M4x4 d9;
	// float cells_4x4f2[4][4] = {
	// 	{1, 2, 8, 0},
	// 	{2, 4, 6, 0},
	// 	{3, 4, 4, 0},
	// 	{4, 2, 1, 1},
	// };
	// d9 = rt::M4x4(cells_4x4f2);
	// if (d8.transpose() == d9) {
	// 	PASS();
	// } else {
	// 	FAIL(test_name);
	// }



	// tests ++;
	// test_name = "rt::M3x3 equality operators";
	// rt::M3x3 e = rt::M3x3();
	// rt::M3x3 e2 = rt::M3x3();
	// e2.data[0][0] = 1;
	// e2.data[1][1] = 1;
	// e2.data[2][2] = 1;
	// if (e == rt::M3x3() 
	// 		&& e != e2) {
	// 			PASS();
	// 		} else {
	// 			FAIL(test_name);
	// }

	// tests ++;
	// test_name = "rt::M3x3 initializers";
	// rt::M3x3 e3 = rt::M3x3();
	// float cells_3x3a[3][3] = {
	// 	{1, 0, 0},
	// 	{0, 1, 0},
	// 	{0, 0, 1}
	// };
	// float cells_3x3b[3][3] = {
	// 	{-62.49,	37.85,	-1.86},
	// 	{-15.82,	-47.48,	45.84},
	// 	{14.01,		-32.78,	-50.00}
	// };
	// e3 = rt::M3x3(cells_3x3a);
	// rt::M3x3 e4 = rt::M3x3(cells_3x3b);
	// if (e2 == e3
	// 		&& e4 == rt::M3x3(cells_3x3b)
	// 		&& e2 != e4) {
	// 			PASS();
	// 		} else {
	// 			FAIL(test_name);
	// }



	// tests ++;
	// test_name = "rt::M2x2 equality operators";
	// rt::M2x2 f = rt::M2x2();
	// rt::M2x2 f2 = rt::M2x2();
	// f2.data[0][0] = 1;
	// f2.data[1][1] = 1;
	// if (f == rt::M2x2() 
	// 		&& f != f2) {
	// 			PASS();
	// 		} else {
	// 			FAIL(test_name);
	// }

	// tests ++;
	// test_name = "rt::M2x2 initializers";
	// rt::M2x2 f3 = rt::M2x2();
	// float cells_2x2a[2][2] = {
	// 	{1, 0},
	// 	{0, 1}
	// };
	// float cells_2x2b[2][2] = {
	// 	{-62.49,	37.85},
	// 	{-15.82,	-47.48}
	// };
	// f3 = rt::M2x2(cells_2x2a);
	// rt::M2x2 f4 = rt::M2x2(cells_2x2b);
	// if (f2 == f3
	// 		&& f4 == rt::M2x2(cells_2x2b)
	// 		&& f2 != f4) {
	// 			PASS();
	// 		} else {
	// 			FAIL(test_name);
	// }

	// tests ++;
	// test_name = "rt::M2x2 determinant";
	// rt::M2x2 f5;
	// float cells_2x2c[2][2] = {
	// 	{ 1, 5},
	// 	{-3, 2}
	// };
	// f5 = rt::M2x2(cells_2x2c);
	// if (is_equal(f5.determinant(), 17)) {
	// 	PASS();
	// } else {
	// 	FAIL(test_name);
	// }

	tests ++;
	test_name = "rt::Matrix equality operators";
	rt::Matrix a = rt::Matrix(4, 4);
	rt::Matrix a2 = rt::Matrix(4, 4);
	a2.data(0, 0) = 1;
	a2.data(1, 1) = 1;
	a2.data(2, 2) = 1;
	a2.data(3, 3) = 1;
	if (a == rt::Matrix(4, 4) 
			&& a != a2
			&& a != rt::Matrix(3, 3)) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Matrix initializers";
	exc_test = true;
	rt::Matrix b = rt::Matrix(4, 4);
	b.init_identity();
	std::vector<float> cells_4x4a = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	std::vector<float> cells_4x4b = {
		-62.49,	 37.85,	-1.86,	 82.44,
		-15.82,	-47.48,	 45.84,	 18.68,
		 14.01,	-32.78,	-50.00,	 27.95,
		-12.96,	 56.62,	 17.05,	-48.98
	};
	try {
		rt::Matrix(3, 3, cells_4x4a);
		exc_test = false;
	} catch(std::invalid_argument err) {
		cout << "CAUGHT error: " << err.what() << endl;
	}
	rt::Matrix b2 = rt::Matrix(4, 4, cells_4x4a);
	rt::Matrix b3 = rt::Matrix(4, 4, cells_4x4b);
	if (b == b2
			&& b3 == rt::Matrix(4, 4, cells_4x4b)
			&& is_equal(b3.data(1, 1), -47.48)
			&& exc_test) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Matrix data access";
	exc_test = true;
	rt::Matrix c = rt::Matrix(4, 4);
	c.init_identity();
	c.data(1, 2) = 12;
	c.data(2, 2) = 22;
	try {
		c.data(3, 4) = 34;
		exc_test = false;
	} catch(std::out_of_range err) {
		cout << "CAUGHT error: " << err.what() << endl;
	}
	try {
		c.data(-1, 3) = -13;
		exc_test = false;
	} catch(std::out_of_range err) {
		cout << "CAUGHT error: " << err.what() << endl;
	}
	
	if (exc_test
			&& is_equal(c.data(1, 2), 12)
			&& is_equal(c.data(2, 2), 22)) {
				PASS();
			} else {
				FAIL(test_name);
	}

	// For completeness, we should probably test other dimensions and non-equal sizes.
	// However, according to the book we should only ever be multiplying 4x4 matrices
	tests ++;
	test_name = "rt::Matrix mul - same size";
	std::vector<float> cells_4x4c = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2
	};
	std::vector<float> cells_4x4d = {
		-2,  1,  2,  3,
		 3,  2,  1, -1,
		 4,  3,  6,  5,
		 1,  2,  7,  8
	};
	std::vector<float> cells_4x4e = {
		20,  22,  50,  48,
		44,  54, 114, 108,
		40,  58, 110, 102,
		16,  26,  46,  42
	};
	rt::Matrix d = rt::Matrix(4, 4, cells_4x4c);
	rt::Matrix d2 = rt::Matrix(4, 4, cells_4x4d);
	if (d.mul(d2) == rt::Matrix(4, 4, cells_4x4e)) {
		PASS();
	} else {
		FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Matrix Point / Vec3 multiplication";
	rt::Point p1 = rt::Point(1, 2, 3);
	rt::Vec3 v1 = rt::Vec3(4, 5, 6);
	std::vector<float> cells_4x4f = {
		1, 2, 3, 4,
		2, 4, 4, 2,
		8, 6, 4, 1,
		0, 0, 0, 1
	};
	rt::Matrix e = rt::Matrix(4, 4, cells_4x4f);
	rt::Matrix e2 = rt::Matrix(4, 4);
	e2.init_identity();
	if (e.mul(p1) == rt::Point(18, 24, 33)
			&& e.mul(v1) == rt::Vec3(32, 52, 86)
			&& e2.mul(p1) == p1
			&& e2.mul(v1) == v1) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Matrix transpose";
	std::vector<float> cells_4x4f2 = {
		1, 2, 8, 0,
		2, 4, 6, 0,
		3, 4, 4, 0,
		4, 2, 1, 1,
	};
	rt::Matrix f = rt::Matrix(4, 4, cells_4x4f2);
	if (e.transpose() == f) {
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