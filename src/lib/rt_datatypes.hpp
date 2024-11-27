/**
 * @file rt_datatypes.hpp
 * @brief The core classes of the raytracer
 * @date 241126
 */

#pragma once

#include <string>
#include "rt_utils.hpp"

namespace rt {

/**
 * @brief A read-only class for returning 4 floats
 */
class Float4 {    
    public:
        Float4(float w_, float x_, float y_, float z_) {
            const float w = w_;
            const float x = x_;
            const float y = y_;
            const float z = z_;
        }
};

/**
 * @brief An XYZ position 
 */
class Point {
    public:
        Point();
        Point(float x, float y, float z);

        // Variables
        float x, y, z;  // Position on axis
                        // These classes are extremely basic datatypes anyway and should be considered accessible,
                        // no need to write protect

        // Methods
        Float4 float4();  // Returns a (W,X,Y,Z) Float4, where W is 1.0
        Point move(Vec3);  // Offset this point by vector, returning the resulting Point.
        Vec3 vec(Point point2);  // Returns the vector from this to point2

        // Operators
        bool operator==(Point);  // Equality check utilizing rtutil::is_equal()
};

/**
 * @brief An XYZ vector
 */
class Vec3 {
    public:
        Vec3();
        Vec3(float x, float y, float z);

        // Variables
        float x, y, z;  // Magnitude of axis
                        // These classes are extremely basic datatypes and should be considered accessible,
                        // no need to write protect

        // Methods
        Float4 float4();  // Returns a (W,X,Y,Z) Float4, where W is 0.0
        Vec3 sub(Vec3 vector2);  // Returns the difference between this and vector2
        Vec3 mult(float);  // Scales the vector uniformly, returning the result
        Vec3 div(float);  // Helper function to scale the vector by 1/float, returning the result
        float mag();  // Returns the magnitude of the vector
        Vec3 normalize();  // Returns a normalized vector
        float dot(Vec3 vector2);  // Returns the dot product of this and vector2
        Vec3 cross(Vec3 vector2);  // Returns the cross product of this and vector2
        
        // Operators
        Vec3 operator-();  // Negates this vector
        Vec3 operator-(Vec3);  // Subtracts another vector from this
        Vec3& operator-=(Vec3);  // Subtracts another vector from this, modified in-place
        Vec3 operator+(Vec3);  // Adds another vector to this
        Vec3& operator+=(Vec3);  // Adds another vector to this, modified in-place
        bool operator==(Vec3);  // Equality check utilizing rtutil::is_equal()
};

}