#ifndef EULER_ROTATIONS_H
#define EULER_ROTATIONS_H

#include <Eigen/Dense>

#include <array>
#include <ostream>
#include <string>

namespace euler
{
  /// Rotation sequence (e.g., xyz, zxz, yxy, etc.)
  using Sequence = std::string;

  /// Euler angles in the same order as the sequence
  using Angles = std::array<double, 3>;

  /// Always orthnonormal 3x3 rotation matrix
  using RotationMatrix = Eigen::Matrix3d;

  /// Always normalized (i.e., unit quaternion)
  using Quaternion = Eigen::Quaterniond;

  /**
   * @brief Order of rotation
   */
  enum class Order
  {
    INTRINSIC,
    EXTRINSIC
  };

  /**
   * @brief Direction of rotation
   */
  enum class Direction
  {
    ACTIVE,
    PASSIVE
  };

  /**
   * @brief Fully describes the conventions used for a rotation
   **/
  struct Convention
  {
    Convention(Order o, Direction d) : order(o), direction(d){};
    const Order order;
    const Direction direction;
  };

  /**
   * @brief Calculates a rotation matrix.
   *
   * @param[in] sequence The sequence of principal axes (e.g., xyz, zxz, etc.)
   * @param[in] angles The three Euler angles in the same order as the sequence
   * @param[in] convention The convention used to generate the rotation matrix
   *
   * @return The resulting rotation matrix
   */
  RotationMatrix getRotationMatrix(const Sequence& sequence,
                                   const Angles& angles, Convention convention);

  /**
   * @brief Converts a quaternion to a rotation matrix. Normalizes the
   * quaternion first.
   *
   * @param[in] q A quaternion representing a rotation
   *
   * @return A rotation matrix representing the same rotation as the input
   * quaternion
   */
  RotationMatrix getRotationMatrix(const Quaternion& q);

  /**
   * @brief Calculates a unit quaternion representing a rotation.
   *
   * @param[in] sequence The sequence of principal axes (e.g., xyz, zxz, etc.)
   * @param[in] angles The three Euler angles in the same order as the sequence
   * @param[in] convention The convention used to generate the rotation matrix
   *
   * @return The resulting unit quaternion
   */
  Quaternion getQuaternion(const Sequence& sequence, const Angles& angles,
                           Convention convention);

  /**
   * @brief Converts a rotation matrix to a unit quaternion.
   *
   * @param[in] R A rotation matrix
   *
   * @return A unit quaternion representing the same rotation as the input
   * rotation matrix
   */
  Quaternion getQuaternion(const RotationMatrix& R);
} // namespace euler

#endif
