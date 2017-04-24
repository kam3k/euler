#include <array>
#include <string>
#include <Eigen/Dense>

namespace euler
{
  namespace internal
  {
    Eigen::Matrix3d Rx(double angle);
    Eigen::Matrix3d Ry(double angle);
    Eigen::Matrix3d Rz(double angle);
    Eigen::Matrix3d Rprincipal(char axis, double angle, bool intrinsic);
  }  // namespace internal
  using Sequence = std::string;
  using Angles = std::array<double, 3>;
  Eigen::Matrix3d rotationMatrix(const Sequence& sequence, const Angles& angles,
                                 bool intrinsic = true);
}  // namespace euler

