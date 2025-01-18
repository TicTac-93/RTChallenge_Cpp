	/**
	 * @file rt_datatypes.hpp
	 * @brief The core classes of the raytracer
	 * @date 2025-1-15
	 */

	#pragma once

	#include <string>
	#include <vector>
	#include "rt_utils.hpp"

	namespace rt {

	class Point;
	class Vec3;
	class Matrix;

	class RGB;

	struct Float4;
	struct MxReturn;

	/**
	 * @brief An XYZ position 
	 */
	class Point {
		public:

			/**
			 * @param x: X Position
			 * @param y: Y Position
			 * @param z: Z Position
			 */
			Point();
			Point(float x, float y, float z);

			// Variables
			float x, y, z;  		// Position on axis
			const float w = 1;	// Used in matrix operations

			// Methods
			/**
			 * @brief Returns Float4(W,X,Y,Z)
			 */
			Float4 float4();

			/**
			 * @brief Returns the vector from here to point2
			 */
			Vec3 vec_to(Point point2);

			/**
			 * @brief Offset this point by X, Y, Z, returning the resulting Point
			 * 
			 * @param x, y, z: Translation to apply
			 * @return Point 
			 */
			Point translate(float x, float y, float z);

			/**
			 * @brief Offset this point by vector, returning the resulting Point
			 */
			Point translate(Vec3 vector);

			/**
			 * @brief Rotates this Point around the origin, returning the resulting Point.
			 * 
			 * 				Rotation is applied in (Z, Y, X) order.
			 * 
			 * @param x, y, z: Rotation in degrees
			 * @return Point 
			 */
			Point rotate(float x, float y, float z);

			/**
			 * @brief Scales the Point relative to the origin, returning the resulting Point.
			 * 
			 * @param x, y, z: Scale factor, where 1.0 is unchanged.
			 * @return Point 
			 */
			Point scale(float x, float y, float z);

			/**
			 * @brief Shears the Point relative to the origin, returning the resulting Point.
			 * 
			 * @param Xy: X shear, Y component
			 * @param Xz: X shear, Z component
			 * @param Yx: Y shear, X component
			 * @param Yz: Y shear, Z component
			 * @param Zx: Z shear, X component
			 * @param Zy: Z shear, Y component
			 * @return Point 
			 */
			Point shear(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy);

			// Operators
			bool operator==(Point);     // Equality check utilizing rtutil::isEqual()
			bool operator!=(Point);     // Equality check utilizing rtutil::isEqual()
	};

	/**
	 * @brief An XYZ vector
	 */
	class Vec3 {
		public:
			Vec3();

			/**
			 * @param x: X Magnitude
			 * @param y: Y Magnitude
			 * @param z: Z Magnitude
			 */
			Vec3(float x, float y, float z);

			// Variables
			float x, y, z;			// Magnitude of axis
			const float w = 0;	// Used in matrix operations

			// Methods
			/**
			 * @brief Returns a Float4(W,X,Y,Z)
			 */
			Float4 float4();
			
			/**
			 * @brief Uniformly multiplies the vector by scalar
			 */
			Vec3 mul(float scalar);

			/**
			 * @brief Uniformly divides the vector by divisor
			 */
			Vec3 div(float divisor);

			/**
			 * @brief Calculates the magnitude of the vector
			 */
			float mag();
			
			/**
			 * @brief Returns a normalized vector, with a magnitude of 1
			 */
			Vec3 normalize();

			/**
			 * @brief Calculates the dot product of this and vector2
			 */
			float dot(Vec3 vector2);

			/**
			 * @brief Calculates the cross product of this and vector2
			 */
			Vec3 cross(Vec3 vector2);

			/**
			 * @brief Rotates the Vector, returning the result.
			 * 
			 * 				Rotation is applied in (Z, Y, X) order.
			 * 
			 * @param x, y, z: Rotation in degrees
			 * @return Vec3 
			 */
			Vec3 rotate(float x, float y, float z);

			/**
			 * @brief Scales the Vector non-uniformly, returning the result.
			 * 
			 * @param x, y, z: Scale factor, where 1.0 is unchanged.
			 * @return Vec3 
			 */
			Vec3 scale(float x, float y, float z);
			
			// Operators
			bool operator==(Vec3);      // Equality check utilizing rtutil::isEqual()
			bool operator!=(Vec3);      // Equality check utilizing rtutil::isEqual()
			Vec3 operator-();           // Negates the vector
			Vec3 operator-(Vec3);       // Subtracts another vector from this
			Vec3& operator-=(Vec3);     // Subtracts another vector from this, modified in-place
			Vec3 operator+(Vec3);       // Adds another vector to this
			Vec3& operator+=(Vec3);     // Adds another vector to this, modified in-place
	};

	class Matrix {
		private:
			const int data_size_;
			std::vector<float> data_;

			/**
			 * @brief Calculates the cofactor of a given cell in the matrix.
			 * 
			 * @param row 
			 * @param col 
			 * @return float
			 */
			float cofactor_at(int row, int col);

		public:
			const int rows, cols;

			/**
			 * @brief Construct a new 4x4 Matrix.  Initially zero-filled.
			 * 
			 * 				The Matrix CAN NOT be resized after construction, if a different size is required
			 * 				call this constructor using (rows, columns) args.
			 * 
			 */
			Matrix();

			/**
			 * @brief Construct a Matrix of variable size.  Initially zero-filled.
			 * 
			 * 				The Matrix CAN NOT be resized after construction, instead make use of methods
			 * 				submatrix() to reduce size
			 * 
			 * @param rows
			 * @param columns
			 */
			Matrix(int rows, int columns);

			/**
			 * @brief Construct a Matrix of variable size.  Initially filled with data from values[] to (0,0), (0,1), (0,2), etc.
			 * 
			 * 				If values[] is not the same size as the Matrix (rows*columns) an invalid_argument exception will be thrown.
			 * 
			 * 				The Matrix CAN NOT be resized after construction, instead make use of methods
			 * 				submatrix() to reduce size
			 * 
			 * @param rows 
			 * @param columns 
			 * @param values: A 1d array of values to initialize the matrix with.  Should be of length (rows * columns).
			 */
			Matrix(int rows, int columns, std::vector <float> values);

			// Accessors
			/**
			 * @brief Provides access to the cells within this Matrix in (row, column) format.
			 * 
			 * 				Will raise out_of_range if the index is invalid.
			 * 
			 * @param row: Zero-based index of row to access
			 * @param col: Zero-based index of column to access
			 * @return float&: Reference to the value in the cell, to read/write
			 */
			float& data(int row, int col);

			// Methods
			// Matrix math methods will be the main means of manipulation
			/**
			 * @brief Initializes this Matrix as an identity matrix.  All existing data will be lost!
			 * 
			 */
			Matrix& init_identity();

			/**
			 * @brief Multiplies this Matrix(A) with another(B), returning the result(AB).
			 * 
			 * 				The number of A's columns must be equal to B's rows. 
			 * 				If the matrices are of different but compatible sizes, the return will be a different size.
			 * 				If the matrices are of incompatible sizes, an invalid_argument exception will be thrown.
			 * 
			 * @param B: the Matrix to multiply this by.
			 * @return Matrix 
			 */
			Matrix mul(Matrix B);

			/**
			 * @brief Multiplies Point p by this matrix, treating it as a 4x1 Matrix.
			 * 				
			 * 				Will throw a logic_error if this is not a 4x4 Matrix.
			 * 
			 * @param p: the Point to be multiplied (transformed) by this Matrix.
			 * @return Point
			 */
			Point mul(Point p);

			/**
			 * @brief Multiplies Vec3 v by this matrix, treating it as a 4x1 Matrix.
			 * 				
			 * 				Will throw a logic_error if this is not a 4x4 Matrix.
			 * 
			 * @param v: the Vec3 to be multiplied (transformed) by this Matrix.
			 * @return Vec3 
			 */
			Vec3 mul(Vec3 v);

			/**
			 * @brief Transposes this matrix, returning the result.
			 * 				Rows become columns, and vice-versa.
			 * 
			 * @return Matrix 
			 */
			Matrix transpose();

			/**
			 * @brief Calculates and returns the determinant of the Matrix.
			 * 				
			 * 				The Matrix must be square, otherwise a logic_error will be thrown.
			 * 
			 * @return float 
			 */
			float determinant();

			/**
			 * @brief Returns a submatrix by removing the given row and column.
			 * 
			 * 				If the row or column is out of range, out_of_range will be thrown.
			 * 				If the matrix is already 2x2, logic_error will be thrown.
			 * 
			 * @param row 
			 * @param col 
			 * @return Matrix 
			 */
			Matrix submatrix(int row, int col);
			
			/**
			 * @brief Calculates the inverse of the Matrix, if possible.  If not, returns FALSE and a blank Matrix.
			 * 
			 * @return MxReturn struct indicating success of the operation, and the resulting Matrix.
			 */
			MxReturn inverse();

			/**
			 * @brief Generates a translation Matrix(B) and then multiplies this*B, returning the result.
			 * 
			 * @param x, y, z: Translation amounts 
			 * @return Matrix 
			 */
			Matrix translate(float x, float y, float z);

			/**
			 * @brief Generates a rotation Matrix(B) and then multiplies this*B, returning the result.
			 * 
			 * 				Rotation is applied in (Z, Y, X) order.
			 * 
			 * @param x, y, z: Rotation in degrees.
			 * @return Matrix 
			 */
			Matrix rotate(float x, float y, float z);

			/**
			 * @brief Generates a scale Matrix(B) and then multiplies this*B, returning the result.
			 * 
			 * @param x, y, z: Scale factor, where 1.0 is unchanged.
			 * @return Matrix 
			 */
			Matrix scale(float x, float y, float z);

			/**
			 * @brief Generates a shearing Matrix(B) and then multiplies this*B, returning the result.
			 * 
			 * @param Xy: X shear, Y component
			 * @param Xz: X shear, Z component
			 * @param Yx: Y shear, X component
			 * @param Yz: Y shear, Z component
			 * @param Zx: Z shear, X component
			 * @param Zy: Z shear, Y component  
			 * @return Matrix 
			 */
			Matrix shear(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy);

			// Operators
			Matrix& operator=(Matrix);	// Copy operator, will throw a runtime_error if the matrices are of different sizes
			bool operator==(Matrix);		// Equality check using rtutil::isEqual() per-cell
			bool operator!=(Matrix);		// Equality check using rtutil::isEqual() per-cell
			Matrix operator*(Matrix);		// Multiplies this Matrix by another, will throw an invalid_argument if they are incompatible
			Matrix& operator*=(Matrix);		// Multiplies this Matrix by another of the same size, in place.  Will throw an invalid_argument if they are incompatible
	};

	/**
	 * @brief An unclamped RGB color value
	 * 
	 * Similar to the Vec3 class but tailored specifically to color operations.
	 * May be expanded in the future to include an Alpha channel
	 */
	class RGB {
		public:
			RGB(float r, float g, float b);
			RGB();

			// Variables
			float r, g, b;  // Color value

			// Methods
			/**
			 * @brief Uniformly multiplies the color by scalar
			 */
			RGB mul(float scalar);

			// Operators
			bool operator==(RGB);   // Equality check utilizing rtutil::isEqual()
			bool operator!=(RGB);   // Equality check utilizing rtutil::isEqual()
			RGB operator+(RGB);     // Adds another color to this
			RGB& operator+=(RGB);   // Adds another color to this, modified in-place
			RGB operator-();        // Negates the color
			RGB operator-(RGB);     // Subtracts another color from this
			RGB& operator-=(RGB);   // Subtracts another color from this, modified in-place
			RGB operator*(RGB);     // Multiplies this with another color
			RGB& operator*=(RGB);   // Multiplies this with another color, modified in-place
	};

	/**
	 * @brief A read-only struct for returning 4 floats
	 */
	// Do we really need this??
	struct Float4 {    
		public:
			Float4(float w, float x, float y, float z);
			const float w, x, y, z;
	};

	/**
	 * @brief Struct for handling Matrix operations that may fail.
	 * 				
	 * @param success: <bool> The success or failure of the matrix operation
	 * 
	 * @param result: <Matrix> The resulting Matrix.  See method documentation for result on failure.
	 */
	struct MxReturn {
		public:
			MxReturn(bool success, Matrix matrix);
			const bool success;
			Matrix result;
	};

	}