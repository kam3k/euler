#ifndef EULER_PRINCIPAL_ROTATIONS_H
#define EULER_PRINCIPAL_ROTATIONS_H

#include <Eigen/Dense>

namespace euler
{
  namespace internal
  {
    Eigen::Matrix3d R_x_passive(double angle);
    Eigen::Matrix3d R_y_passive(double angle);
    Eigen::Matrix3d R_z_passive(double angle);
    Eigen::Matrix3d R_principal(char axis, double angle, bool use_active);
  }  // namespace internal
} // namespace euler

#endif
