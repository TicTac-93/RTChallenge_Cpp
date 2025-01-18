/**
 * @file rt_datatypes.cpp
 * @brief Implementations for core classes
 * @date 2025-1-15
 */

#include "rt_datatypes.hpp"
#include "rt_transforms.hpp"
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

rt::Vec3 rt::Point::vec_to(rt::Point point2) {
	// p1 - p2 produces a back-vector from p2->p1, so we do p2 - p1 to get p1->p2
	return rt::Vec3(point2.x - x, point2.y - y, point2.z - z);
}

rt::Point rt::Point::translate(rt::Vec3 vector) {
	return rt::Point(x + vector.x, y + vector.y, z + vector.z);
}

rt::Point rt::Point::translate(float in_x, float in_y, float in_z) {
	return rt::Point(x + in_x, y + in_y, z + in_z);
}

rt::Point rt::Point::rotate(float in_x, float in_y, float in_z) {
	rt::Matrix xform = rt::rotate(in_x, in_y, in_z);
	return xform.mul(*this);
}

rt::Point rt::Point::scale(float in_x, float in_y, float in_z) {
	return rt::Point(x * in_x, y * in_y, z * in_z);
}

rt::Point rt::Point::shear(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy) {
	rt::Matrix xform = rt::shear(Xy, Xz, Yx, Yz, Zx, Zy);
	return xform.mul(*this);
}

bool rt::Point::operator==(rt::Point point2) {
	if (rtutil::isEqual(x, point2.x) &&
		rtutil::isEqual(y, point2.y) &&
		rtutil::isEqual(z, point2.z)) {

		return true;
	} else {
		return false;
	}        
}

bool rt::Point::operator!=(rt::Point point2) {
	if (rtutil::isEqual(x, point2.x) &&
		rtutil::isEqual(y, point2.y) &&
		rtutil::isEqual(z, point2.z)) {

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

rt::Vec3 rt::Vec3::rotate(float in_x, float in_y, float in_z) {
	rt::Matrix xform = rt::rotate(in_x, in_y, in_z);
	return xform.mul(*this);
}

rt::Vec3 rt::Vec3::scale(float in_x, float in_y, float in_z) {
	return rt::Vec3(x * in_x, y * in_y, z * in_z);
}

bool rt::Vec3::operator==(rt::Vec3 vector2) {
	if (rtutil::isEqual(x, vector2.x) &&
			rtutil::isEqual(y, vector2.y) &&
			rtutil::isEqual(z, vector2.z)) {

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

// Matrix
// ===============
rt::Matrix::Matrix()
	: rows{4}
	, cols{4}
	, data_size_{16}
{
	data_.resize(data_size_);
	data_.shrink_to_fit();
	for (int i = 0; i < data_size_; i++) {
		data_[i] = 0;
	}
}

rt::Matrix::Matrix(int in_rows, int in_columns)
	: rows{in_rows}
	,	cols{in_columns}
	, data_size_{in_rows * in_columns}
{
	data_.resize(data_size_);
	data_.shrink_to_fit();
	for (int i = 0; i < data_size_; i++) {
		data_[i] = 0;
	}
}

rt::Matrix::Matrix(int in_rows, int in_columns, std::vector<float> values)
	: rows{in_rows}
	,	cols{in_columns}
	, data_size_{in_rows * in_columns}
{
	if (values.size() != data_size_) {
		std::string msg = "Length of values arg (" + std::to_string(values.size())
											+ ") does not match number of cells (" + std::to_string(data_size_) + ")";
		throw(std::invalid_argument(msg));
	}

	data_.resize(data_size_);
	data_.shrink_to_fit();
	for (int i = 0; i < data_size_; i++) {
		data_[i] = values[i];
	}
}

float& rt::Matrix::data(int row, int col) {
	if (row >= rows
			|| col >= cols
			|| row < 0
			|| col < 0) {
				std::string msg = "Matrix[" + std::to_string(rows) + "x" + std::to_string(cols) +
													"] index [" + std::to_string(row) + ", " + std::to_string(col) + "] INVALID!";
				throw std::out_of_range(msg);
	}
	// Data is stored in 1d vector, row by row
	return data_[(row * cols) + col];
}

rt::Matrix& rt::Matrix::init_identity() {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (r == c) {
				data(r, c) = 1;
			} else {
				data(r, c) = 0;
			}
		}
	}

	return *this;
}

rt::Matrix rt::Matrix::mul(rt::Matrix B) {
	// Validate matrices
	if (cols != B.rows) {
		std::string msg = "Cannot multiply matrices of size [" + std::to_string(rows) + "," + std::to_string(cols)
											+ "] and [" + std::to_string(B.rows) + ", " + std::to_string(B.cols) + "]";
		throw(std::invalid_argument(msg));
	}

	int out_rows = rows;
	int out_cols = B.cols;
	rt::Matrix output = rt::Matrix(out_rows, out_cols);
	float val;

	// Iterate over each cell in the output Matrix
	for (int r = 0; r < out_rows; r++) {
		for (int c = 0; c < out_cols; c++) {
			val = 0;  // Reset val for each cell calculation
			for (int i = 0; i < cols; i++) {
				// Calculate the output value, one combination at a time.
				// (r, 0) * (0, c)  +  (r, 1) * (1, c)  +  ...
				val += (data(r, i) * B.data(i, c));
			}
			output.data(r, c) = val;
		}
	}

	return output;
}

rt::Point rt::Matrix::mul(rt::Point p) {
	// Validate this matrix (can be 3x3, 4x3, or 4x4)
	if (cols < 3
			|| cols > 4
			|| rows < 3
			|| rows > 4) {
				std::string msg = "Cannot multiply matrix of size [" + std::to_string(rows) + "," + std::to_string(cols)
													+ "] and a Point";
				throw(std::invalid_argument(msg));		
	}

	rt::Point output = rt::Point();
	float xyz[4];
	float val;
	int c;

	xyz[0] = p.x;
	xyz[1] = p.y;
	xyz[2] = p.z;
	xyz[3] = p.w;

	// Iterate over each value in the output Point
	// X
	val = 0;  // Reset val
	for (int i = 0; i < cols; i++) {
		// Calculate the output value, one combination at a time.
		val += (data(0, i) * xyz[i]);
	}
	output.x = val;

	// Y
	val = 0;  // Reset val
	for (int i = 0; i < cols; i++) {
		// Calculate the output value, one combination at a time.
		val += (data(1, i) * xyz[i]);
	}
	output.y = val;

	// Z
	val = 0;  // Reset val
	for (int i = 0; i < cols; i++) {
		// Calculate the output value, one combination at a time.
		val += (data(2, i) * xyz[i]);
	}
	output.z = val;

	// We won't worry about W, assume it's still 1

	return output;
}

rt::Vec3 rt::Matrix::mul(rt::Vec3 v) {
	// Validate this matrix (can be 3x3, 4x3, or 4x4)
	if (cols < 3
			|| cols > 4
			|| rows < 3
			|| rows > 4) {
				std::string msg = "Cannot multiply matrix of size [" + std::to_string(rows) + "," + std::to_string(cols)
													+ "] and a Vec3";
				throw(std::invalid_argument(msg));		
	}

	rt::Vec3 output = rt::Vec3();
	float xyz[4];
	float val;
	int c;

	xyz[0] = v.x;
	xyz[1] = v.y;
	xyz[2] = v.z;
	xyz[3] = v.w;

	// Iterate over each value in the output Point
	// X
	val = 0;  // Reset val
	for (int i = 0; i < cols; i++) {
		// Calculate the output value, one combination at a time.
		val += (data(0, i) * xyz[i]);
	}
	output.x = val;

	// Y
	val = 0;  // Reset val
	for (int i = 0; i < cols; i++) {
		// Calculate the output value, one combination at a time.
		val += (data(1, i) * xyz[i]);
	}
	output.y = val;

	// Z
	val = 0;  // Reset val
	for (int i = 0; i < cols; i++) {
		// Calculate the output value, one combination at a time.
		val += (data(2, i) * xyz[i]);
	}
	output.z = val;

	// We won't worry about W, assume it's still 0

	return output;
}

rt::Matrix rt::Matrix::transpose() {
	rt::Matrix output = rt::Matrix(cols, rows);

	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			output.data(c, r) = data(r, c);
		}
	}

	return output;
}

float rt::Matrix::cofactor_at(int row, int col) {
	// Set the cofactor sign for this cell to pos or neg
	// "Odd" cells are negative (0,1), (1,2), (3,0), etc
	int sign = (row + col) % 2 == 0 ? 1 : -1;
	return(sign * submatrix(row, col).determinant());
}

float rt::Matrix::determinant() {
	if (rows != cols) {
		throw(std::logic_error("Cannot calculate determinant of a non-square matrix!"));
	}

	float output = 0;

	// Handle larger matrices recursively
	if (cols > 2) {
		for (int c = 0; c < cols; c++) {
			output += (
					data(0, c)  // This cell's value
				* cofactor_at(0, c)
			);
		}

	// Eventually they'll be whittled down to 2x2
	} else {
		output = (
				data(0, 0) * data(1, 1)
			-	data(0, 1) * data(1, 0)
		);
	}

	return output; 
}

rt::Matrix rt::Matrix::submatrix(int row, int col) {
	if (row < 0
			|| col < 0
			|| row > rows
			|| col > cols) {
				std::string msg = "Cannot get submatrix at [" + std::to_string(row) + ", " + std::to_string(col) + "]";
				throw(std::out_of_range(msg));
	} else if (rows <= 2 || cols <= 2) {
		throw(std::logic_error("Matrix is too small to be subdivided!"));
	}

	rt::Matrix m_out = rt::Matrix(rows - 1, cols - 1);
	int r_out, c_out;

	r_out = 0;
	for (int r = 0; r < rows; r++) {
		// Skip the indicated row
		if (r == row) {
			continue;
		}

		c_out = 0;
		for (int c = 0; c < cols; c++) {
			// Skip the indicated column
			if (c == col) {
				continue;
			}
			m_out.data(r_out, c_out) = data(r, c);
			c_out ++;
		}
		r_out ++;
	}

	return m_out;
}

rt::MxReturn rt::Matrix::inverse() {
	rt::Matrix M_inv = rt::Matrix(rows, cols);
	if (rows != cols) {
		return rt::MxReturn(false, M_inv);  // Squares only
	}

	float det = determinant();
	if (rtutil::isEqual(det, 0)) {
		return rt::MxReturn(false, M_inv);  // Matrix is uninvertable
	}

	// Calculate cofactor of each cell
	// Divide by determinant of the matrix
	// Transpose
	// We'll combine a few steps here to avoid unnecessarily creating class instances
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			// Transpose as we go by placing (r, c) into (c, r)
			M_inv.data(c, r) = (cofactor_at(r, c) / det);
		}
	}
	return rt::MxReturn(true, M_inv);
}

rt::Matrix rt::Matrix::translate(float in_x, float in_y, float in_z) {
	if (rows != 4 || cols != 4) {
		throw std::runtime_error("Cannot apply transforms to a non-4x4 Matrix!");
	}

	return mul(rt::translate(in_x, in_y, in_z));
}

rt::Matrix rt::Matrix::rotate(float in_x, float in_y, float in_z) {
	if (rows != 4 || cols != 4) {
		throw std::runtime_error("Cannot apply transforms to a non-4x4 Matrix!");
	}

	return mul(rt::rotate(in_x, in_y, in_z));
}

rt::Matrix rt::Matrix::scale(float in_x, float in_y, float in_z) {
	if (rows != 4 || cols != 4) {
		throw std::runtime_error("Cannot apply transforms to a non-4x4 Matrix!");
	}

	return mul(rt::scale(in_x, in_y, in_z));
}

rt::Matrix rt::Matrix::shear(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy) {
	if (rows != 4 || cols != 4) {
		throw std::runtime_error("Cannot apply transforms to a non-4x4 Matrix!");
	}

	return mul(rt::shear(Xy, Xz, Yx, Yz, Zx, Zy));
}

rt::Matrix& rt::Matrix::operator=(rt::Matrix m2) {
	if (rows != m2.rows
			|| cols != m2.cols) {
				throw(std::runtime_error("Cannot copy matrices of different sizes"));
	}
	memcpy(&data_, &m2.data_, sizeof(data_));

	return *this;
}

bool rt::Matrix::operator==(rt::Matrix m2) {
	if (rows != m2.rows
			|| cols != m2.cols) {
				return false;
	}

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if ( !rtutil::isEqual(data(r, c), m2.data(r, c)) ) {
				return false;
			}
		}
	}
	return true;
}

bool rt::Matrix::operator!=(rt::Matrix m2) {
	return !(*this == m2);
}

rt::Matrix rt::Matrix::operator*(rt::Matrix B) {
	return mul(B);
}

rt::Matrix& rt::Matrix::operator*=(rt::Matrix B) {
	if (rows != B.rows
			|| cols != B.cols) {
				throw std::invalid_argument("Cannot use *= with matrices of different sizes!  Use Matrix.mul() instead");
	}

	rt::Matrix result = mul(B);
	*this = result;
	return *this;
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
	if (rtutil::isEqual(r, color2.r) &&
			rtutil::isEqual(g, color2.g) &&
			rtutil::isEqual(b, color2.b)) {

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


// MxRETURN
rt::MxReturn::MxReturn(bool in_success, rt::Matrix in_result)
	: success(in_success)
	, result(in_result) {}
