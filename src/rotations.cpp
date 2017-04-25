#include <internal/principal_rotations.h>
#include <rotations.h>

namespace euler
{
  RotationMatrix getRotationMatrix(const Sequence& sequence, const Angles& angles,
                                bool use_extrinsic, bool use_active)
  {
    assert(sequence.size() == 3);
    assert(angles.size() == 3);

    if (use_extrinsic)
    {
      return internal::R_principal(sequence[2], angles[2], use_active) *
             internal::R_principal(sequence[1], angles[1], use_active) *
             internal::R_principal(sequence[0], angles[0], use_active);
    }
    else  // intrinsic
    {
      return internal::R_principal(sequence[0], angles[0], use_active) *
             internal::R_principal(sequence[1], angles[1], use_active) *
             internal::R_principal(sequence[2], angles[2], use_active);
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
