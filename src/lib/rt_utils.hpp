/**
 * @file rt_utils.hpp
 * @brief A set of utility functions for the raytracer
 * @date 241126
 */

const float kFLOAT_MARGIN = 0.00001f;

namespace rtutil {

/**
 * @brief Test two floats for equality, within a small margin of error
 */
bool is_equal(float a, float b);

}