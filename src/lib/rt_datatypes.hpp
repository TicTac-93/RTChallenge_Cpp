	/**
	 * @file rt_datatypes.hpp
	 * @brief The core classes of the raytracer
	 * @date 241230
	 */

	#pragma once

	#include <string>
	#include "rt_utils.hpp"

	namespace rt {

	class Point;
	class Vec3;
	class M4x4;

	class RGB;

	struct Float4;

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
			float x, y, z;  // Position on axis

			// Methods
			/**
			 * @brief Returns Float4(W,X,Y,Z), where W is 1.0
			 */
			Float4 float4();

			/**
			 * @brief Offset this point by vector, returning the resulting Point
			 */
			Point move(Vec3 vector);

			/**
			 * @brief Returns the vector from here to point2
			 */
			Vec3 vec_to(Point point2);

			// Operators
			bool operator==(Point);     // Equality check utilizing rtutil::is_equal()
			bool operator!=(Point);     // Equality check utilizing rtutil::is_equal()
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
			float x, y, z;  // Magnitude of axis

			// Methods
			/**
			 * @brief Returns a Float4(W,X,Y,Z), where W is 0
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
			
			// Operators
			bool operator==(Vec3);      // Equality check utilizing rtutil::is_equal()
			bool operator!=(Vec3);      // Equality check utilizing rtutil::is_equal()
			Vec3 operator-();           // Negates the vector
			Vec3 operator-(Vec3);       // Subtracts another vector from this
			Vec3& operator-=(Vec3);     // Subtracts another vector from this, modified in-place
			Vec3 operator+(Vec3);       // Adds another vector to this
			Vec3& operator+=(Vec3);     // Adds another vector to this, modified in-place
	};

	/**
	 * @brief A 4x4 Matrix of floats
	 */
	class M4x4 {
		private:
		/**
		 * @brief Copy the data from Matrix m2 to this
		 * 
		 * @param m2: The matrix to be copied
		 */
			void copy_(M4x4 m2);
			
		public:
			/**
			 * @brief Initializes a new zeroed out 4x4 Matrix
			 */
			M4x4();

			/**
			 * @brief Initializes a new 4x4 Matrix using 2d array values
			 * @param values: A 4x4 array of values to initialize with
			 */
			M4x4(float values[4][4]);

			// Variables
			float data[4][4] {
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0},
				{0, 0, 0, 0}
			};

			// Methods
			// Matrix math methods will be the main means of manipulation
			/**
			 * @brief Convenience function to set this up as an Identity Matrix.
			 *				This will clear any data previously entered!
			 */
			void init_identity();

			/**
			 * @brief Multiplies this matrix with another 4x4 matrix.
			 * 
			 * @param m2: the matrix to be multiplied with.
			 * @return M4x4 
			 */
			M4x4 mul(M4x4 m2);

			// TODO: Multiplication of Point and Vec3

			// Operators
			bool operator==(M4x4);		// Equality check utilizing rtutil::is_equal() per cell
			bool operator!=(M4x4);		// Equality check utilizing rtutil::is_equal() per cell
			M4x4 operator*(M4x4);			// Multiplies this with another 4x4 Matrix
			M4x4& operator*=(M4x4);		// Multiplies this with another 4x4 Matrix, modified in place
	};

	/**
	 * @brief A 3x3 Matrix of floats
	 */
	class M3x3 {
		public:
			/**
			 * @brief Initializes a new, zeroed out 3x3 Matrix
			 */
			M3x3();
			
			/**
			 * @brief Initializes a new 3x3 Matrix using 2d array values
			 * @param values: A 3x3 array of values to initialize with
			 */
			M3x3(float[3][3]);

			// Variables
			float data[3][3] {
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0}
			};

			// Methods
			// Matrix math methods will be the main means of manipulation

			// Operators
			bool operator==(M3x3);		// Equality check utilizing rtutil::is_equal() per cell
			bool operator!=(M3x3);		// Equality check utilizing rtutil::is_equal() per cell
	};

	/**
	 * @brief A 2x2 Matrix of floats
	 */
	class M2x2 {
		public:
			/**
			 * @brief Initializes a new, zeroed out 3x3 Matrix
			 */
			M2x2();
			
			/**
			 * @brief Initializes a new 2x2 Matrix using 2d array values
			 * @param values: A 2x2 array of values to initialize with
			 */
			M2x2(float[2][2]);

			// Variables
			float data[2][2] {
				{0, 0},
				{0, 0}
			};

			// Methods
			// Matrix math methods will be the main means of manipulation

			// Operators
			bool operator==(M2x2);		// Equality check utilizing rtutil::is_equal() per cell
			bool operator!=(M2x2);		// Equality check utilizing rtutil::is_equal() per cell
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
			bool operator==(RGB);   // Equality check utilizing rtutil::is_equal()
			bool operator!=(RGB);   // Equality check utilizing rtutil::is_equal()
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
	struct Float4 {    
		public:
			Float4(float w, float x, float y, float z);
			const float w, x, y, z;
	};

	}