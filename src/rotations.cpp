#include <euler/rotations.h>

#include <cassert>
#include <cmath>

namespace euler
{
  namespace
  {
    RotationMatrix R_active_x(double angle)
    {
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      RotationMatrix ret;
      // clang-format off
      ret << 1,  0,  0,
             0,  c, -s,
             0,  s,  c;
      // clang-format on
      return ret;
    }

    RotationMatrix R_active_y(double angle)
    {
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      RotationMatrix ret;
      // clang-format off
      ret << c,  0,  s,
             0,  1,  0,
            -s,  0,  c;
      // clang-format on
      return ret;
    }

    RotationMatrix R_active_z(double angle)
    {
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      RotationMatrix ret;
      // clang-format off
      ret << c, -s,  0,
             s,  c,  0,
             0,  0,  1;
      // clang-format on
      return ret;
    }

    RotationMatrix R_active(char axis, double angle)
    {
      assert(axis == 'x' || axis == 'y' || axis == 'z');

      RotationMatrix R;
      switch (axis)
      {
        case 'x':
          R = R_active_x(angle);
          break;
        case 'y':
          R = R_active_y(angle);
          break;
        case 'z':
          R = R_active_z(angle);
          break;
      }
      return R;
    }
  } // namespace

  RotationMatrix getRotationMatrix(const Sequence& sequence,
                                   const Angles& angles, Convention convention)
  {
    assert(sequence.size() == 3);
    assert(angles.size() == 3);

    RotationMatrix R;

    if (convention.order == Order::INTRINSIC)
    {
      R = R_active(sequence[0], angles[0]) * R_active(sequence[1], angles[1]) *
          R_active(sequence[2], angles[2]);
    }
    else // extrinsic
    {
      R = R_active(sequence[2], angles[2]) * R_active(sequence[1], angles[1]) *
          R_active(sequence[0], angles[0]);
    }

    if (convention.direction == Direction::PASSIVE)
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
                           Convention convention)
  {
    return Quaternion(getRotationMatrix(sequence, angles, convention))
        .normalized();
  }

  Quaternion getQuaternion(const RotationMatrix& R)
  {
    return Quaternion(R).normalized();
  }
} // namespace euler
