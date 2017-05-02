#ifndef EULER_IO_H
#define EULER_IO_H

#include <iostream>
#include <Eigen/Geometry>
#include <euler/rotations.h>

std::ostream& operator<<(std::ostream& os, const euler::Quaternion& q);

namespace euler
{
  bool isSequenceValid(const Sequence& sequence);

  bool areAnglesValid(const Angles& angles);
} // namespace euler

#endif
