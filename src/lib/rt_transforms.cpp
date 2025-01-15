/**
 * @file rt_transforms.cpp
 * @author Josh H
 * @brief Implementations for transformation functions
 * @date 2025-01-15
 */

#include "rt_transforms.hpp"
#include "rt_datatypes.hpp"
#include "rt_utils.hpp"
#include <math.h>
#include <string>

rt::Matrix rt::translate(float in_x, float in_y, float in_z) {
  rt::Matrix output = rt::Matrix(4, 4);
  output.init_identity();
  output.data(0, 3) = in_x;
  output.data(1, 3) = in_y;
  output.data(2, 3) = in_z;
  
  return output;
}

rt::Matrix rt::rotate(float in_x, float in_y, float in_z) {
  // Set up each matrix as an identity matrix
  rt::Matrix rot_x = rt::Matrix(4, 4);
  rot_x.init_identity();
  rt::Matrix rot_y = rot_x;
  rt::Matrix rot_z = rot_x;

  // 0-degree rotations do not alter the identity matrix, and can be skipped
  // Do not use rtutil::isEqual, we do not want to discard extremely small rotations

  if (in_x != 0) {
    float cos_x = cos(rtutil::degToRad(in_x));
    float sin_x = sin(rtutil::degToRad(in_x));
    rot_x.data(1, 1) = cos_x;
    rot_x.data(2, 2) = cos_x;
    rot_x.data(1, 2) = -sin_x;
    rot_x.data(2, 1) = sin_x;
  }

  if (in_y != 0) {
    float cos_y = cos(rtutil::degToRad(in_y));
    float sin_y = sin(rtutil::degToRad(in_y));
    rot_y.data(0, 0) = cos_y;
    rot_y.data(0, 2) = sin_y;
    rot_y.data(2, 0) = -sin_y;
    rot_y.data(2, 2) = cos_y;
  }

  if (in_z != 0) {
    float cos_z = cos(rtutil::degToRad(in_z));
    float sin_z = sin(rtutil::degToRad(in_z));
    rot_z.data(0, 0) = cos_z;
    rot_z.data(0, 1) = -sin_z;
    rot_z.data(1, 0) = sin_z;
    rot_z.data(1, 1) = cos_z;
  }

  return (rot_z * rot_y * rot_x);
}

rt::Matrix rt::scale(float in_x, float in_y, float in_z) {
  rt::Matrix output = rt::Matrix(4, 4);
  output.data(0, 0) = in_x;
  output.data(1, 1) = in_y;
  output.data(2, 2) = in_z;
  output.data(3, 3) = 1;

  return output;
}

rt::Matrix rt::shear(float Xy, float Xz, float Yx, float Yz, float Zx, float Zy) {
  rt::Matrix output = rt::Matrix(4, 4);
  output.init_identity();

  output.data(0,1) = Xy;
  output.data(0,2) = Xz;
  output.data(1,0) = Yx;
  output.data(1,2) = Yz;
  output.data(2,0) = Zx;
  output.data(2,1) = Zy;

  return output;
}
