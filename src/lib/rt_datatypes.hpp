/**
 * @file rt_datatypes.hpp
 * @brief The core classes of the raytracer
 * @date 241126
 */

#pragma once

#include <string>
#include "rt_utils.hpp"

namespace rt {

class Point;
class Vec3;
class Float4;
class RGB;

/**
 * @brief An XYZ position 
 */
class Point {
    public:
        Point(float x, float y, float z);
        Point();

        // Variables
        float x, y, z;  // Position on axis
                        // These classes are extremely basic datatypes anyway and should be considered accessible,
                        // no need to write protect

        // Methods
        Float4 float4();            // Returns a (W,X,Y,Z) Float4, where W is 1.0
        Point move(Vec3);           // Offset this point by vector, returning the resulting Point.
        Vec3 vec_to(Point point2);  // Returns the vector from this to point2

        // Operators
        bool operator==(Point);     // Equality check utilizing rtutil::is_equal()
        bool operator!=(Point);     // Equality check utilizing rtutil::is_equal()
};

/**
 * @brief An XYZ vector
 */
class Vec3 {
    public:
        Vec3(float x, float y, float z);
        Vec3();

        // Variables
        float x, y, z;  // Magnitude of axis
                        // These classes are extremely basic datatypes and should be considered accessible,
                        // no need to write protect

        // Methods
        Float4 float4();            // Returns a (W,X,Y,Z) Float4, where W is 0.0
        Vec3 mul(float scalar);     // Uniformly multiplies the vector by scalar
        Vec3 div(float divisor);    // Uniformly divides the vector by divisor
        float mag();                // Returns the magnitude of the vector
        Vec3 normalize();           // Returns a normalized vector
        float dot(Vec3 vector2);    // Returns the dot product of this and vector2
        Vec3 cross(Vec3 vector2);   // Returns the cross product of this and vector2
        
        // Operators
        Vec3 operator-();           // Negates the vector
        Vec3 operator-(Vec3);       // Subtracts another vector from this
        Vec3& operator-=(Vec3);     // Subtracts another vector from this, modified in-place
        Vec3 operator+(Vec3);       // Adds another vector to this
        Vec3& operator+=(Vec3);     // Adds another vector to this, modified in-place
        bool operator==(Vec3);      // Equality check utilizing rtutil::is_equal()
        bool operator!=(Vec3);      // Equality check utilizing rtutil::is_equal()
};

/**
 * @brief A read-only class for returning 4 floats
 */
class Float4 {    
    public:
        Float4(float w, float x, float y, float z);
        const float w, x, y, z;
};

/**
 * @brief An unclamped RGB color value
 * 
 * Similar to the Vec3 class but tailored specifically to color operations.
 * Will be expanded in the future to include an Alpha channel
 */
class RGB {
    public:
        RGB(float r, float g, float b);
        RGB();

        // Variables
        float r, g, b;  // Color value

        // Methods
        RGB mul(float scalar);  // Uniformly scales the color by scalar

        // Operators
        RGB operator+(RGB);     // Adds another color to this
        RGB& operator+=(RGB);   // Adds another color to this, modified in-place
        RGB operator-();        // Negates the color
        RGB operator-(RGB);     // Subtracts another color from this
        RGB& operator-=(RGB);   // Subtracts another color from this, modified in-place
        RGB operator*(RGB);     // Multiplies this with another color
        RGB& operator*=(RGB);   // Multiplies this with another color, modified in-place
        bool operator==(RGB);   // Equality check utilizing rtutil::is_equal()
        bool operator!=(RGB);   // Equality check utilizing rtutil::is_equal()
};

}