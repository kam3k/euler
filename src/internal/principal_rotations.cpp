#include <internal/principal_rotations.h>
#include <cassert>
#include <cmath>

namespace euler
{
  namespace internal
  {
    Eigen::Matrix3d R_x_passive(double angle)
    {
      Eigen::Matrix3d ret;
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      ret << 1,  0, 0,
             0,  c, s,
             0, -s, c;
      return ret;
    }

    Eigen::Matrix3d R_y_passive(double angle)
    {
      Eigen::Matrix3d ret;
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      ret << c, 0, -s,
             0, 1,  0,
             s, 0,  c;
      return ret;
    }

    Eigen::Matrix3d R_z_passive(double angle)
    {
      Eigen::Matrix3d ret;
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      ret << c, s, 0,
            -s, c, 0,
             0, 0, 1;
      return ret;
    }

    Eigen::Matrix3d R_principal(char axis, double angle, bool use_active)
    {
      assert(axis == 'x' || axis == 'y' || axis == 'z');

      Eigen::Matrix3d R;
      switch (axis)
      {
        case 'x':
          R = R_x_passive(angle);
          break;
        case 'y':
          R = R_y_passive(angle);
          break;
        case 'z':
          R = R_z_passive(angle);
          break;
      }

      if (use_active)
      {
        R.transposeInPlace();
      }

      return R;
    }
  } // namespace internal
} // namespace euler
