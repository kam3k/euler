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
      // clang-format off
      RotationMatrix ret = {1.0,  0.0,  0.0,
                            0.0,    c,   -s,
                            0.0,    s,    c};
      // clang-format on
      return ret;
    }

    RotationMatrix R_active_y(double angle)
    {
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      // clang-format off
      RotationMatrix ret = {  c,  0.0,    s,
                            0.0,  1.0,  0.0,
                             -s,  0.0,    c};
      // clang-format on
      return ret;
    }

    RotationMatrix R_active_z(double angle)
    {
      const auto c = std::cos(angle);
      const auto s = std::sin(angle);
      // clang-format off
      RotationMatrix ret = {  c,   -s,  0.0,
                              s,    c,  0.0,
                            0.0,  0.0,  1.0};
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

  RotationMatrix operator*(const RotationMatrix& lhs, const RotationMatrix& rhs)
  {
    return {lhs[0] * rhs[0] + lhs[1] * rhs[3] + lhs[2] * rhs[6],
            lhs[0] * rhs[1] + lhs[1] * rhs[4] + lhs[2] * rhs[7],
            lhs[0] * rhs[2] + lhs[1] * rhs[5] + lhs[2] * rhs[8],
            lhs[3] * rhs[0] + lhs[4] * rhs[3] + lhs[5] * rhs[6],
            lhs[3] * rhs[1] + lhs[4] * rhs[4] + lhs[5] * rhs[7],
            lhs[3] * rhs[2] + lhs[4] * rhs[5] + lhs[5] * rhs[8],
            lhs[6] * rhs[0] + lhs[7] * rhs[3] + lhs[8] * rhs[6],
            lhs[6] * rhs[1] + lhs[7] * rhs[4] + lhs[8] * rhs[7],
            lhs[6] * rhs[2] + lhs[7] * rhs[5] + lhs[8] * rhs[8]};
  }

  RotationMatrix transpose(const RotationMatrix& R)
  {
    // clang-format off
    return {R[0], R[3], R[6], 
            R[1], R[4], R[7], 
            R[2], R[5], R[8]};
    // clang-format on
  }

  RotationMatrix toRotationMatrix(const Sequence& sequence,
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

    return (convention.direction == Direction::ACTIVE) ? R : transpose(R);
  }

  Quaternion toQuaternion(const RotationMatrix& R)
  {
    Quaternion q;
    q[0] = std::sqrt(std::max(0.0, 1.0 + R[0] + R[4] + R[8])) / 2.0;

    q[1] = std::sqrt(std::max(0.0, 1.0 + R[0] - R[4] - R[8])) / 2.0;
    q[1] = std::copysign(q[1], R[7] - R[5]);

    q[2] = std::sqrt(std::max(0.0, 1.0 - R[0] + R[4] - R[8])) / 2.0;
    q[2] = std::copysign(q[2], R[2] - R[6]);

    q[3] = std::sqrt(std::max(0.0, 1.0 - R[0] - R[4] + R[8])) / 2.0;
    q[3] = std::copysign(q[3], R[3] - R[1]);
    return q;
  }
} // namespace euler
