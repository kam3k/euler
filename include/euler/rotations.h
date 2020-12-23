#ifndef EULER_ROTATIONS_H
#define EULER_ROTATIONS_H

#include <array>
#include <ostream>
#include <string>

namespace euler {
/// Rotation sequence (e.g., xyz, zxz, yxy, etc.)
using Sequence = std::string;

/// Euler angles in the same order as the sequence
using Angles = std::array<double, 3>;

/// 3x3 roation matrix stored in row-major order
using RotationMatrix = std::array<double, 9>;

/// Unit quaternion stored in w, x, y, z order
using Quaternion = std::array<double, 4>;

/**
 * @brief Order of rotation
 */
enum class Order { INTRINSIC, EXTRINSIC };

/**
 * @brief Direction of rotation
 */
enum class Direction { ACTIVE, PASSIVE };

/**
 * @brief Fully describes the conventions used for a rotation
 **/
struct Convention {
  Convention(Order o, Direction d) : order(o), direction(d){};
  const Order order;
  const Direction direction;
};

/**
 * @brief Multiplication operation of two rotation matrices
 *
 * @param[in] lhs Left-hand side matrix
 * @param[in] rhs Right-hand side matrix
 *
 * @return Rotation matrix resulting from lhs * rhs
 */
RotationMatrix operator*(const RotationMatrix& lhs, const RotationMatrix& rhs);

/**
 * @brief Transpose of rotation matrix (same as inverse)
 *
 * @param[in] R Rotation matrix to transpose
 *
 * @return Transpose of R
 */
RotationMatrix transpose(const RotationMatrix& R);

/**
 * @brief Converts an euler angle sequence to a rotation matrix
 *
 * @param[in] sequence The sequence of principal axes (e.g., xyz, zxz, etc.)
 * @param[in] angles The three Euler angles in the same order as the sequence
 * @param[in] convention The convention used to generate the rotation matrix
 *
 * @return The resulting rotation matrix
 */
RotationMatrix toRotationMatrix(const Sequence& sequence, const Angles& angles,
                                Convention convention);

/**
 * @brief Converts a rotation matrix (assumed to be orthonormal) to the unit quaternion that
 * parametizes the equivalent rotation
 *
 * @details Uses algorithm suggested by Christian here:
 * http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
 *
 * @param[in] R Rotation matrix to convert to a unit quaternion
 *
 * @return Unit quaternion parameterization of R
 */
Quaternion toQuaternion(const RotationMatrix& R);

}  // namespace euler

#endif
