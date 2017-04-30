#ifndef EULER_ROTATIONS_H
#define EULER_ROTATIONS_H

#include <Eigen/Dense>
#include <array>
#include <ostream>
#include <string>

namespace euler
{
  using Sequence = std::string;
  using Angles = std::array<double, 3>;
  using RotationMatrix = Eigen::Matrix3d;
  using Quaternion = Eigen::Quaterniond;

  RotationMatrix getRotationMatrix(const Sequence& sequence,
                                   const Angles& angles, bool is_intrinsic,
                                   bool is_active);

  RotationMatrix getRotationMatrix(const Quaternion& q);

  Quaternion getQuaternion(const Sequence& sequence, const Angles& angles,
                           bool is_intrinsic, bool is_active);

  Quaternion getQuaternion(const RotationMatrix& R);
}  // namespace euler

#endif
