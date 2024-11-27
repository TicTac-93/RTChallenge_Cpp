/**
 * @file rt_utils.cpp
 * @brief Implementations of utility functions
 * @date 241126
 */

#include "rt_utils.hpp"

bool rtutil::is_equal(float a, float b) {
    float x = a-b;
    if (x < 0) {
        x = -x;
    }
    return (x < kFLOAT_MARGIN) ? true : false;
}