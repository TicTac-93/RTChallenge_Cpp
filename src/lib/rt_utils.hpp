/**
 * @file rt_utils.hpp
 * @brief A set of utility functions for the raytracer
 * @date 2025-1-15
 */

#pragma once

const float kFLOAT_MARGIN = 0.00001f;
const double kPI = 3.14159265358979;
const double kRECIP_180 = 0.00555555555555;

namespace rtutil {

/**
 * @brief Test two floats for equality, within a small margin of error
 * 
 * @param a, b: Float value to be compared
 */
bool isEqual(float a, float b);

/**
 * @brief Converts degrees to radians
 * 
 * @param degrees
 * @return double Radians
 */
double degToRad(double degrees);

}