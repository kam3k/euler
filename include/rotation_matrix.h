#ifndef EULER_ROTATION_MATRIX_H
#define EULER_ROTATION_MATRIX_H

#include <array>
#include <string>
#include <Eigen/Dense>

namespace euler
{
  using Sequence = std::string;
  using Angles = std::array<double, 3>;
  Eigen::Matrix3d rotationMatrix(const Sequence& sequence, const Angles& angles,
                                 bool use_extrinsic = false);
}  // namespace euler

#endif
