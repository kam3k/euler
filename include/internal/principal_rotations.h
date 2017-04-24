#ifndef EULER_PRINCIPAL_ROTATIONS_H
#define EULER_PRINCIPAL_ROTATIONS_H

#include <Eigen/Dense>

namespace euler
{
  namespace internal
  {
    Eigen::Matrix3d Rx(double angle);
    Eigen::Matrix3d Ry(double angle);
    Eigen::Matrix3d Rz(double angle);
    Eigen::Matrix3d Rprincipal(char axis, double angle, bool intrinsic);
  }  // namespace internal
} // namespace euler

#endif
