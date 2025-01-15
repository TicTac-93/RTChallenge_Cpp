/**
 * @file rt_utils.cpp
 * @brief Implementations of utility functions
 * @date 2025-1-15
 */

#include "rt_utils.hpp"

bool rtutil::isEqual(float a, float b) {
    float x = a-b;
    if (x < 0) {
        x = -x;
    }
    return (x < kFLOAT_MARGIN) ? true : false;
}

double rtutil::degToRad(double deg) {
    // (deg / 180) * pi
    // deg * (1/180) * pi
    return ( deg * kRECIP_180 * kPI );
}