#include <rotations.h>
#include <internal/principal_rotations.h>

namespace euler
{
  Eigen::Matrix3d rotationMatrix(const Sequence& sequence, const Angles& angles,
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
    else // intrinsic
    {
      return internal::R_principal(sequence[0], angles[0], use_active) *
             internal::R_principal(sequence[1], angles[1], use_active) *
             internal::R_principal(sequence[2], angles[2], use_active);
    }

  }
}  // namespace euler
