/**
 * @file rt_datatypes.cpp
 * @brief Implementations for core classes
 * @date 241126
 */

#include "rt_datatypes.hpp"
#include <string>

// POINT
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
    return Float4(0.0f, x, y, z);
}

rt::Point::operator std::string() {
    // Probably want to clean this up and limit to a few decimal places
    std::string output = "(" + std::to_string(x) + ", "
                             + std::to_string(y) + ", "
                             + std::to_string(z) + ")";
}

// VEC3
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
    return Float4(0.0f, x, y, z);
}

rt::Vec3::operator std::string() {
    // Probably want to clean this up and limit to a few decimal places
    std::string output = "(" + std::to_string(x) + ", "
                             + std::to_string(y) + ", "
                             + std::to_string(z) + ")";
}

// FLOAT4
rt::Float4::Float4(float in_w, float in_x, float in_y, float in_z) {
    w_ = in_w;
    x_ = in_x;
    y_ = in_y;
    z_ = in_z;
}

rt::Float4::operator std::string() {
    // Probably want to clean this up and limit to a few decimal places
    std::string output = "(" + std::to_string(w_) + ", "
                             + std::to_string(x_) + ", "
                             + std::to_string(y_) + ", "
                             + std::to_string(z_) + ")";
}