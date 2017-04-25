#ifndef EULER_ROTATIONS_H
#define EULER_ROTATIONS_H

#include <array>
#include <string>
#include <Eigen/Dense>
#include <ostream>

namespace euler
{
  using Sequence = std::string;
  using Angles = std::array<double, 3>;
  using RotationMatrix = Eigen::Matrix3d;
  using Quaternion = Eigen::Quaterniond;

  RotationMatrix getRotationMatrix(const Sequence& sequence,
                                   const Angles& angles, bool use_extrinsic,
                                   bool use_active);

  RotationMatrix getRotationMatrix(const Quaternion& q);

  Quaternion getQuaternion(const Sequence& sequence, const Angles& angles,
                           bool use_extrinsic, bool use_active);

  Quaternion getQuaternion(const RotationMatrix& R);
}  // namespace euler

#endif
