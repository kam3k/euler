#include <euler/rotations.h>
#include <cassert>
#include <cmath>

namespace euler
{
  namespace 
  {
    Eigen::Matrix3d R_x_active(double angle)
    {
      Eigen::Matrix3d ret;
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      ret << 1,  0,  0,
             0,  c, -s,
             0,  s,  c;
      return ret;
    }

    Eigen::Matrix3d R_y_active(double angle)
    {
      Eigen::Matrix3d ret;
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      ret << c,  0,  s,
             0,  1,  0,
            -s,  0,  c;
      return ret;
    }

    Eigen::Matrix3d R_z_active(double angle)
    {
      Eigen::Matrix3d ret;
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      ret << c, -s,  0,
             s,  c,  0,
             0,  0,  1;
      return ret;
    }

    Eigen::Matrix3d R_active(char axis, double angle)
    {
      assert(axis == 'x' || axis == 'y' || axis == 'z');

      Eigen::Matrix3d R;
      switch (axis)
      {
        case 'x':
          R = R_x_active(angle);
          break;
        case 'y':
          R = R_y_active(angle);
          break;
        case 'z':
          R = R_z_active(angle);
          break;
      }
      return R;
    }
  } // namespace

  RotationMatrix getRotationMatrix(const Sequence& sequence,
                                   const Angles& angles, bool is_intrinsic,
                                   bool is_active)
  {
    assert(sequence.size() == 3);
    assert(angles.size() == 3);

    Eigen::Matrix3d R;

    if (is_intrinsic)
    {
      R = R_active(sequence[0], angles[0]) *
          R_active(sequence[1], angles[1]) *
          R_active(sequence[2], angles[2]);
    }
    else  // extrinsic
    {
      R = R_active(sequence[2], angles[2]) *
          R_active(sequence[1], angles[1]) *
          R_active(sequence[0], angles[0]);
    }

    if (!is_active)
    {
      R.transposeInPlace();
    }

    return R;
  }

  RotationMatrix getRotationMatrix(const Quaternion& q)
  {
    return q.normalized().toRotationMatrix();
  }

  Quaternion getQuaternion(const Sequence& sequence, const Angles& angles,
                           bool is_intrinsic, bool is_active)
  {
    return Quaternion(
               getRotationMatrix(sequence, angles, is_intrinsic, is_active))
        .normalized();
  }

  Quaternion getQuaternion(const RotationMatrix& R)
  {
    return Quaternion(R).normalized();
  }
}  // namespace euler
