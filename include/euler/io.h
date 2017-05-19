#ifndef EULER_IO_H
#define EULER_IO_H

#include <iostream>
#include <Eigen/Geometry>
#include <euler/rotations.h>

namespace euler
{
  bool isSequenceValid(const Sequence& sequence);

  void prettyPrint(const RotationMatrix& R);

  void prettyPrint(const Quaternion& q);
} // namespace euler

#endif
