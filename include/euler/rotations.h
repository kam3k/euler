#ifndef EULER_ROTATIONS_H
#define EULER_ROTATIONS_H

#include <Eigen/Dense>
#include <array>
#include <ostream>
#include <string>

namespace euler
{
  using Sequence = std::string;
  using Angles = std::array<double, 3>;
  using RotationMatrix = Eigen::Matrix3d;
  using Quaternion = Eigen::Quaterniond;

  enum class Order
  {
    INTRINSIC,
    EXTRINSIC
  };

  enum class Direction
  {
    ACTIVE,
    PASSIVE
  };

  struct Convention
  {
    Convention(Order o, Direction d) : order(o), direction(d){};
    const Order order;
    const Direction direction;
  };

  RotationMatrix getRotationMatrix(const Sequence& sequence,
                                   const Angles& angles, Convention convention);

  RotationMatrix getRotationMatrix(const Quaternion& q);

  Quaternion getQuaternion(const Sequence& sequence, const Angles& angles,
                           Convention convention);

  Quaternion getQuaternion(const RotationMatrix& R);
}  // namespace euler

#endif
