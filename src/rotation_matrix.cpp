#include <rotation_matrix.h>
#include <internal/principal_rotations.h>

namespace euler
{
  Eigen::Matrix3d rotationMatrix(const Sequence& sequence, const Angles& angles,
                                 bool intrinsic /* = true */)
  {
    assert(sequence.size() == 3);
    assert(angles.size() == 3);

    return internal::Rprincipal(sequence[2], angles[2], intrinsic) *
           internal::Rprincipal(sequence[1], angles[1], intrinsic) *
           internal::Rprincipal(sequence[0], angles[0], intrinsic);
  }
}  // namespace euler
