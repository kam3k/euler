#include <internal/principal_rotations.h>
#include <cassert>
#include <cmath>

namespace euler
{
  namespace internal
  {
    Eigen::Matrix3d Rx(double angle)
    {
      Eigen::Matrix3d ret;
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      ret << 1,  0, 0,
             0,  c, s,
             0, -s, c;
      return ret;
    }

    Eigen::Matrix3d Ry(double angle)
    {
      Eigen::Matrix3d ret;
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      ret << c, 0, -s,
             0, 1,  0,
             s, 0,  c;
      return ret;
    }

    Eigen::Matrix3d Rz(double angle)
    {
      Eigen::Matrix3d ret;
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      ret << c, s, 0,
            -s, c, 0,
             0, 0, 1;
      return ret;
    }

    Eigen::Matrix3d Rprincipal(char axis, double angle, bool use_extrinsic)
    {
      assert(axis == 'x' || axis == 'y' || axis == 'z');

      Eigen::Matrix3d R;
      switch (axis)
      {
        case 'x':
          R = Rx(angle);
          break;
        case 'y':
          R = Ry(angle);
          break;
        case 'z':
          R = Rz(angle);
          break;
      }

      if (use_extrinsic)
      {
        R.transposeInPlace();
      }

      return R;
    }
  } // namespace internal
} // namespace euler
