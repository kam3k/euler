#include <euler/rotations.h>
#include <cassert>
#include <cmath>

namespace euler
{
  namespace 
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
  } // namespace

  RotationMatrix getRotationMatrix(const Sequence& sequence, const Angles& angles,
                                bool use_extrinsic, bool use_active)
  {
    assert(sequence.size() == 3);
    assert(angles.size() == 3);

    if (use_extrinsic)
    {
      return R_principal(sequence[2], angles[2], use_active) *
             R_principal(sequence[1], angles[1], use_active) *
             R_principal(sequence[0], angles[0], use_active);
    }
    else  // intrinsic
    {
      return R_principal(sequence[0], angles[0], use_active) *
             R_principal(sequence[1], angles[1], use_active) *
             R_principal(sequence[2], angles[2], use_active);
    }
  }

  RotationMatrix getRotationMatrix(const Quaternion& q)
  {
    return q.normalized().toRotationMatrix();
  }

  Quaternion getQuaternion(const Sequence& sequence, const Angles& angles,
                        bool use_extrinsic, bool use_active)
  {
    return Quaternion(
               getRotationMatrix(sequence, angles, use_extrinsic, use_active))
        .normalized();
  }

  Quaternion getQuaternion(const RotationMatrix& R)
  {
    return Quaternion(R).normalized();
  }
}  // namespace euler
