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
	cout << "\nUNIT TEST - rt::Matrix" << endl;

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
	test_name = "rt::Matrix initializers [1 exc checks]";
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
		cout << "CAUGHT error 1/1: " << err.what() << endl;
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
	test_name = "rt::Matrix data access [2 exc checks]";
	exc_test = true;
	rt::Matrix c = rt::Matrix(4, 4);
	c.init_identity();
	c.data(1, 2) = 12;
	c.data(2, 2) = 22;
	try {
		c.data(3, 4) = 34;
		exc_test = false;
	} catch(std::out_of_range err) {
		cout << "CAUGHT error 1/2: " << err.what() << endl;
	}
	try {
		c.data(-1, 3) = -13;
		exc_test = false;
	} catch(std::out_of_range err) {
		cout << "CAUGHT error 2/2: " << err.what() << endl;
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
		4, 2, 1, 1
	};
	rt::Matrix f = rt::Matrix(4, 4, cells_4x4f2);
	if (e.transpose() == f) {
		PASS();
	} else {
		FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Matrix submatrix [3 exc checks]";
	exc_test = true;
	std::vector<float> cells_4x4h1 = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 0, 1, 2,
		3, 4, 5, 6
	};
	std::vector<float> cells_3x3h2 = {
		1, 2, 4,
		9, 0, 2,
		3, 4, 6
	};
	rt::Matrix h1 = rt::Matrix(4, 4, cells_4x4h1);
	rt::Matrix h2 = rt::Matrix(3, 3, cells_3x3h2);

	try {
		h1.submatrix(0, 4);
		exc_test = false;
	} catch(std::out_of_range err) {
		cout << "CAUGHT error 1/3: " << err.what() << endl;
	}
	try {
		h2.submatrix(-1, 0);
		exc_test = false;
	} catch(std::out_of_range err) {
		cout << "CAUGHT error 2/3: " << err.what() << endl;
	}
	try {
		h2.submatrix(0, 0).submatrix(0, 0);
		exc_test = false;
	} catch(std::logic_error err) {
		cout << "CAUGHT error 3/3: " << err.what() << endl;
	}

	if (h1.submatrix(1, 2) == h2
			&& exc_test) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Matrix determinant";
	std::vector<float> cells_i1_2x2 = {
		 1, 5,
		-3, 2
	};
	std::vector<float> cells_i2_3x3 = {
		 1,  2,  6,
		-5,  8, -4,
		 2,  6,  4
	};
	std::vector<float> cells_i3_4x4 = {
		-2, -8,  3,  5,
		-3,  1,  7,  3,
		 1,  2, -9,  6,
		-6,  7,  7, -9
	};
	rt::Matrix i1 = rt::Matrix(2, 2, cells_i1_2x2);
	rt::Matrix i2 = rt::Matrix(3, 3, cells_i2_3x3);
	rt::Matrix i3 = rt::Matrix(4, 4, cells_i3_4x4);
	if (is_equal(i1.determinant(), 17)
			&& is_equal(i2.determinant(), -196)
			&& is_equal(i3.determinant(), -4071)) {
				PASS();
			} else {
				cout << "i1 " << i1.determinant() << "\ni2 " << i2.determinant() << "\ni3 " << i3.determinant() << endl;
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Matrix inverse";
	std::vector<float> cells_j1_4x4 = {
		 6,  4,  4,  4,
		 5,  5,  7,  6,
		 4, -9,  3, -7,
		 9,  1,  7, -6
	};
	std::vector<float> cells_j2_4x4 = {
		-4,  2, -2, -3,
		 9,  6,  2,  6,
		 0, -5,  1, -5,
		 0,  0,  0,  0
	};
	std::vector<float> cells_j3_4x4 = {
		-5,  2,  6, -8,
		 1, -5,  1,  8,
		 7,  7, -6, -7,
		 1, -3,  7,  4
	};
	std::vector<float> cells_j4b_4x4 = {
		  0.21805,  0.45113,  0.24060, -0.04511,
		 -0.80827, -1.45677, -0.44361,  0.52068,
		 -0.07895, -0.22368, -0.05263,  0.19737,
		 -0.52256, -0.81391, -0.30075,  0.30639
	};
	rt::Matrix j1 = rt::Matrix(4, 4, cells_j1_4x4);
	rt::Matrix j2 = rt::Matrix(4, 4, cells_j2_4x4);
	rt::Matrix j3 = rt::Matrix(4, 4, cells_j3_4x4);
	rt::Matrix j4 = rt::Matrix(4, 4);
	rt::Matrix j4b = rt::Matrix(4, 4, cells_j4b_4x4);
	j4 = j3.inverse().result;
	if (j4 == j4b
			&& j1.inverse().success
			&& !j2.inverse().success) {
				PASS();
			} else {
				FAIL(test_name);
	}

	tests ++;
	test_name = "rt::Matrix inverse - additional tests";
	std::vector<float> cells_k1_4x4 = {
		 8, -5,  9,  2,
		 7,  5,  6,  1,
		-6,  0,  9,  6,
		-3,  0, -9, -4
	};
	std::vector<float> cells_k1b_4x4 = {
		-0.15385, -0.15385, -0.28205, -0.53846,
		-0.07692,  0.12308,  0.02564,  0.03077,
		 0.35897,  0.35897,  0.43590,  0.92308,
		-0.69231, -0.69231, -0.76923, -1.92308
	};

	std::vector<float> cells_k2_4x4 = {
		 9,  3,  0,  9,
		-5, -2, -6, -3,
		-4,  9,  6,  4,
		-7,  6,  6,  2
	};
	std::vector<float> cells_k2b_4x4 = {
		-0.04074, -0.07778,  0.14444, -0.22222,
		-0.07778,  0.03333,  0.36667, -0.33333,
		-0.02901, -0.14630, -0.10926,  0.12963,
		 0.17778,  0.06667, -0.26667,  0.33333
	};

	std::vector<float> cells_k3_4x4 = {
		 3, -9,  7, 3,
		 3, -8,  2, -9,
		-4,  4,  4,  1,
		-6,  5, -1,  1
	};
	std::vector<float> cells_k4_4x4 = {
		 8,  2,  2,  2,
		 3, -1,  7,  0,
		 7,  0,  5,  4,
		 6, -2,  0,  5
	};

	rt::Matrix k1 = rt::Matrix(4, 4, cells_k1_4x4);
	rt::Matrix k1b = rt::Matrix(4, 4, cells_k1b_4x4);
	rt::Matrix k2 = rt::Matrix(4, 4, cells_k2_4x4);
	rt::Matrix k2b = rt::Matrix(4, 4, cells_k2b_4x4);
	rt::Matrix k3 = rt::Matrix(4, 4, cells_k3_4x4);
	rt::Matrix k4 = rt::Matrix(4, 4, cells_k4_4x4);
	rt::Matrix k5 = k3.mul(k4);													// k3 * k4
	if (k1.inverse().result == k1b
			&& k2.inverse().result == k2b
			&& (k5.mul(k4.inverse().result) == k3)) {
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