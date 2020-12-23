#ifndef EULER_IO_H
#define EULER_IO_H

#include <euler/rotations.h>

#include <iostream>

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
   * @brief Pretty print the element of a quaternion
   * 
   * @param[in] os Stream to print in
   * @param[in] q Quaternion to print
   * 
   * @return Update stream
   */
  std::ostream& operator<<(std::ostream& os, const euler::Quaternion& q);

  /** 
   * @brief Pretty print the element of a rotation matrix
   * 
   * @param[in] os Stream to print in
   * @param[in] q Rotation matrix to print
   * 
   * @return Update stream
   */
  std::ostream& operator<<(std::ostream& os, const euler::RotationMatrix& R);

} // namespace euler

#endif
