/**
 * @file rt_transforms.hpp
 * @author Josh H
 * @brief A collection of xform functions
 * @date 2025-01-15 
 */

#pragma once

#include "rt_datatypes.hpp"
#include "rt_utils.hpp"

namespace rt {

/**
 * @brief Generates a 4x4 xform matrix to translate a given distance.
 * 
 * @param x, y, z: Translation distance
 * @return Matrix 4x4
 */
Matrix translate(float x, float y, float z);

/**
 * @brief Generates a 4x4 xform matrix to rotate a given amount in degrees, in (Z, Y, X) order
 * 
 * @param x, y, z: Rotation in degrees
 * @return Matrix 4x4
 */
Matrix rotate(float x, float y, float z);

/**
 * @brief Generates a 4x4 xform matrix to scale a given amount.  Negative values are allowed.
 * 
 * @param x, y, z: Scale factor, 1 being neutral
 * @return Matrix 4x4
 */
Matrix scale(float x, float y, float z);

/**
 * @brief Generates an xform matrix to shear along each axis a given amount relative to the other axes.
 * 
 * @param Xy: X shear, Y component
 * @param Xz: X shear, Z component
 * @param Yx: Y shear, X component
 * @param Yz: Y shear, Z component
 * @param Zx: Z shear, X component
 * @param Zy: Z shear, Y component  
 * @return Matrix 4x4
 */
Matrix shear(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy);

}