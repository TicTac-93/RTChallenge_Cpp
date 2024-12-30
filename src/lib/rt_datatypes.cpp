/**
 * @file rt_datatypes.cpp
 * @brief Implementations for core classes
 * @date 241230
 */

#include "rt_datatypes.hpp"
#include "rt_utils.hpp"
#include <string>
#include <math.h>
#include <stdexcept>


// POINT
// ===============
rt::Point::Point() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

rt::Point::Point(float in_x, float in_y, float in_z) {
	x = in_x;
	y = in_y;
	z = in_z;
}

rt::Float4 rt::Point::float4() {
	return rt::Float4(1.0f, x, y, z);
}

rt::Point rt::Point::move(rt::Vec3 vector) {
	return rt::Point(x + vector.x, y + vector.y, z + vector.z);
}

rt::Vec3 rt::Point::vec_to(rt::Point point2) {
	// p1 - p2 produces a back-vector from p2->p1, so we do p2 - p1 to get p1->p2
	return rt::Vec3(point2.x - x, point2.y - y, point2.z - z);
}

bool rt::Point::operator==(rt::Point point2) {
	if (rtutil::is_equal(x, point2.x) &&
		rtutil::is_equal(y, point2.y) &&
		rtutil::is_equal(z, point2.z)) {

		return true;
	} else {
		return false;
	}        
}

bool rt::Point::operator!=(rt::Point point2) {
	if (rtutil::is_equal(x, point2.x) &&
		rtutil::is_equal(y, point2.y) &&
		rtutil::is_equal(z, point2.z)) {

		return false;
	} else {
		return true;
	}        
}


// VEC3
// ===============
rt::Vec3::Vec3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

rt::Vec3::Vec3(float in_x, float in_y, float in_z) {
	x = in_x;
	y = in_y;
	z = in_z;
}

rt::Float4 rt::Vec3::float4() {
	return rt::Float4(0.0f, x, y, z);
}

rt::Vec3 rt::Vec3::mul(float scalar) {
	return rt::Vec3(x * scalar, y * scalar, z * scalar);    
}

rt::Vec3 rt::Vec3::div(float divisor) {
	if (divisor == 0) {
		throw std::runtime_error("Cannot divide vector by zero!");
	}
	return mul(1 / divisor);
}

float rt::Vec3::mag() {
	// Magnitude is simple to calculate for a 3D vector.
	// x^2 + y^2 gives us a^2, the horizontal distance (squared)
	// a^2 + z^2 gives us mag^2.
	// Therefore, we can just sum the squares of X, Y, Z, and then root them
	return sqrt(x*x + y*y + z*z);
}

rt::Vec3 rt::Vec3::normalize() {
	// Returns a vector clamped -1 to 1
	return div(mag());
}

float rt::Vec3::dot(rt::Vec3 vector2) {
	// Returns the Cos of the two vectors.
	// 1 = aligned, 0 = 90deg off, -1 = opposite
	// Haven't really wrapped my head around the math yet
	return(x * vector2.x +
		   y * vector2.y +
		   z * vector2.z);
}

rt::Vec3 rt::Vec3::cross(rt::Vec3 vector2) {
	// Returns a new Vec3 perpendicular to both of the inputs
	// Haven't really warpped my head around the math yet
	return rt::Vec3(y * vector2.z  -  z * vector2.y,
					z * vector2.x  -  x * vector2.z,
					x * vector2.y  -  y * vector2.x);
}

bool rt::Vec3::operator==(rt::Vec3 vector2) {
	if (rtutil::is_equal(x, vector2.x) &&
			rtutil::is_equal(y, vector2.y) &&
			rtutil::is_equal(z, vector2.z)) {

		return true;
	} else {
		return false;
	}        
}

bool rt::Vec3::operator!=(rt::Vec3 vector2) {
	return !(*this == vector2);
}

rt::Vec3 rt::Vec3::operator-() {
	return rt::Vec3(-x, -y, -z);
}

rt::Vec3 rt::Vec3::operator-(rt::Vec3 vector2) {
	return rt::Vec3(x - vector2.x, y - vector2.y, z - vector2.z);
}

rt::Vec3& rt::Vec3::operator-=(rt::Vec3 vector2) {
	x -= vector2.x;
	y -= vector2.y;
	z -= vector2.z;
	return *this; 
}

rt::Vec3 rt::Vec3::operator+(rt::Vec3 vector2) {
	return rt::Vec3(x + vector2.x, y + vector2.y, z + vector2.z);
}

rt::Vec3& rt::Vec3::operator+=(rt::Vec3 vector2) {
	x += vector2.x;
	y += vector2.y;
	z += vector2.z;
	return *this; 
}

// M4x4
// ===============
rt::M4x4::M4x4() {}

rt::M4x4::M4x4(float values[4][4]) {
	for (int r=0; r<4; r++) {
		for (int c=0; c<4; c++) {
			data[r][c] = values[r][c];
		}
	}
}

void rt::M4x4::copy_(rt::M4x4 m2) {
	for (int r=0; r<4; r++) {
		for (int c=0; c<4; c++) {
			data[r][c] = m2.data[r][c];
		}
	}
}

void rt::M4x4::init_identity() {
	for (int r=0; r<4; r++) {
		for (int c=0; c<4; c++) {
			if (r == c) {
				data[r][c] = 1;
			} else {
				data[r][c] = 0;
			}
		}
	}
}

rt::M4x4 rt::M4x4::mul(rt::M4x4 m2) {
	rt::M4x4 output = rt::M4x4();

	for (int r=0; r<4; r++) {
		for (int c=0; c<4; c++) {
			output.data[r][c] = (
					(data[r][0] * m2.data[0][c])
				+ (data[r][1] * m2.data[1][c])
				+ (data[r][2] * m2.data[2][c])
				+ (data[r][3] * m2.data[3][c])
			);
		}
	}

	return output;
}

bool rt::M4x4::operator==(rt::M4x4 m2) {
	for (int r=0; r<4; r++) {
		for (int c=0; c<4; c++) {
			if ( !rtutil::is_equal(data[r][c], m2.data[r][c]) ) {
				return false;
			}
		}
	}
	return true;
}

bool rt::M4x4::operator!=(rt::M4x4 m2) {
	return !(*this == m2);
}

rt::M4x4 rt::M4x4::operator*(rt::M4x4 m2) {
	return mul(m2);
}

rt::M4x4& rt::M4x4::operator*=(rt::M4x4 m2) {
	copy_(mul(m2));
	return *this;
}

// M3x3
// ===============
rt::M3x3::M3x3() {}

/**
 * Initialize the matrix with data from cells
 */
rt::M3x3::M3x3(float values[3][3]) {
	for (int r=0; r<3; r++) {
		for (int c=0; c<3; c++) {
			data[r][c] = values[r][c];
		}
	}
}

bool rt::M3x3::operator==(M3x3 m2) {
	for (int r=0; r<3; r++) {
		for (int c=0; c<3; c++) {
			if ( !rtutil::is_equal(data[r][c], m2.data[r][c]) ) {
				return false;
			}
		}
	}
	return true;
}

bool rt::M3x3::operator!=(M3x3 m2) {
	return !(*this == m2);
}

// M2x2
// ===============
rt::M2x2::M2x2() {}

/**
 * Initialize the matrix with data from cells
 */
rt::M2x2::M2x2(float values[2][2]) {
	for (int r=0; r<2; r++) {
		for (int c=0; c<2; c++) {
			data[r][c] = values[r][c];
		}
	}
}

bool rt::M2x2::operator==(M2x2 m2) {
	for (int r=0; r<2; r++) {
		for (int c=0; c<2; c++) {
			if ( !rtutil::is_equal(data[r][c], m2.data[r][c]) ) {
				return false;
			}
		}
	}
	return true;
}

bool rt::M2x2::operator!=(M2x2 m2) {
	return !(*this == m2);
}


// RGB
// ===============
rt::RGB::RGB() {
	r = 0;
	g = 0;
	b = 0;
}

rt::RGB::RGB(float r_in, float g_in, float b_in) {
	r = r_in;
	g = g_in;
	b = b_in;
}

rt::RGB rt::RGB::mul(float scalar) {
	return rt::RGB(r * scalar, g * scalar, b * scalar);
}

bool rt::RGB::operator==(rt::RGB color2) {
	if (rtutil::is_equal(r, color2.r) &&
			rtutil::is_equal(g, color2.g) &&
			rtutil::is_equal(b, color2.b)) {

		return true;
	} else {
		return false;
	}
}

bool rt::RGB::operator!=(rt::RGB color2) {
	return !(*this == color2);
}

rt::RGB rt::RGB::operator+(rt::RGB color2) {
	return rt::RGB(r + color2.r, g + color2.g, b + color2.b);
}

rt::RGB& rt::RGB::operator+=(rt::RGB color2) {
	r += color2.r;
	g += color2.g;
	b += color2.b;
	return *this;
}

rt::RGB rt::RGB::operator-() {
	return rt::RGB(-r, -g, -b);
}

rt::RGB rt::RGB::operator-(rt::RGB color2) {
	return rt::RGB(r - color2.r, g - color2.g, b - color2.b);    
}

rt::RGB& rt::RGB::operator-=(rt::RGB color2) {
	r -= color2.r;
	g -= color2.g;
	b -= color2.b;
	return *this;    
}

rt::RGB rt::RGB::operator*(rt::RGB color2) {
	return rt::RGB(r * color2.r, g * color2.g, b * color2.b);
}

rt::RGB& rt::RGB::operator*=(rt::RGB color2) {
	r *= color2.r;
	g *= color2.g;
	b *= color2.b;
	return *this;
}


// FLOAT4
// ===============
rt::Float4::Float4(float in_w, float in_x, float in_y, float in_z)
	: w(in_w),
	  x(in_x),
	  y(in_y),
	  z(in_z) {}
