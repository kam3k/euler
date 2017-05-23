#ifndef EULER_IO_H
#define EULER_IO_H

#include <iostream>
#include <Eigen/Geometry>
#include <euler/rotations.h>

namespace euler
{
  /**
   * @brief Determines if a given sequence is a valid sequence of axes from
   * which a rotation matrix and unit quaternion can be calculated.
   *
   * @param[in] sequence A string that potentially represents a rotation
   * sequence
   *
   * @return True if the input sequence is a valid rotation sequence, false
   * otherwise.
   */
  bool isSequenceValid(const Sequence& sequence);

  /**
   * @brief Prints a rotation matrix to the console nicely (i.e., reasonable
   * number of decimal places, columns are aligned).
   *
   * @param[in] R The rotation matrix to print.
   */
  void prettyPrint(const RotationMatrix& R);

  /**
   * @brief Print a quaternion to the console nicely (i.e., reasonable number of
   * decimal places, the name of each element is given).
   *
   * @param[in] q The quaternion to print.
   */
  void prettyPrint(const Quaternion& q);
} // namespace euler

#endif
