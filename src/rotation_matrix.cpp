#include <rotation_matrix.h>
#include <internal/principal_rotations.h>

namespace euler
{
  Eigen::Matrix3d rotationMatrix(const Sequence& sequence, const Angles& angles,
                                 bool use_extrinsic /* = false */)
  {
    assert(sequence.size() == 3);
    assert(angles.size() == 3);

    return internal::Rprincipal(sequence[2], angles[2], use_extrinsic) *
           internal::Rprincipal(sequence[1], angles[1], use_extrinsic) *
           internal::Rprincipal(sequence[0], angles[0], use_extrinsic);
  }
}  // namespace euler
