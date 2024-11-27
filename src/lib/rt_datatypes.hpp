/**
 * @file rt_datatypes.hpp
 * @brief The core classes of the raytracer
 * @date 241126
 */

#include <string>

namespace rt {

/**
 * @brief A simple class for XYZ position 
 */
class Point {
    public:
        Point();
        Point(float x, float y, float z);

        // Variables
        float x, y, z;  // Live a little, don't write-protect these values
                        // These classes are extremely basic datatypes anyway, and should be considered accessible

        // Methods
        Float4 float4();

        operator std::string();
};

/**
 * @brief A simple class for 3D vectors
 */
class Vec3 {
    public:
        Vec3();
        Vec3(float x, float y, float z);

        // Variables
        float x, y, z;  // Live a little, don't write-protect these values
                        // These classes are extremely basic datatypes anyway, and should be considered accessible

        // Methods
        Float4 float4();
        
        operator std::string();
};

/**
 * @brief A simple read-only class for returning 4 floats
 */
class Float4 {
    private:
        float w_, x_, y_, z_;
    
    public:
        Float4(float w, float x, float y, float z);

        float w() {
            return w_;
        }
        float x() {
            return x_;
        }
        float y() {
            return y_;
        }
        float z() {
            return z_;
        }

        operator std::string();

};

}