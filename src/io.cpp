#include <euler/io.h>

#include <algorithm>
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const euler::Quaternion& q)
{
  // clang-format off
  os << std::fixed << std::setprecision(4) 
     << " w: " << std::setw(7) << q[0] << "\n"
     << " x: " << std::setw(7) << q[1] << "\n"
     << " y: " << std::setw(7) << q[2] << "\n"
     << " z: " << std::setw(7) << q[3] << "\n";
  // clang-format on
  return os;
}

namespace euler
{
  bool isSequenceValid(const Sequence& seq)
  {
    if (seq.length() != 3)
    {
      return false;
    }

    std::array<std::string, 12> sequences = {"xyz", "xzy", "yxz", "yzx",
                                             "zxy", "zyx", "xyx", "xzx",
                                             "yxy", "yzy", "zxz", "zyz"};
    return std::find(std::begin(sequences), std::end(sequences), seq) !=
           std::end(sequences);
  }

  void prettyPrint(const RotationMatrix& R)
  {
    // clang-format off
    std::cout << "Rotation Matrix:\n"
      << std::fixed << std::setprecision(4)
      << std::setw(8) << R[0]
      << std::setw(8) << R[1]
      << std::setw(8) << R[2] << "\n"
      << std::setw(8) << R[3]
      << std::setw(8) << R[4]
      << std::setw(8) << R[5] << "\n"
      << std::setw(8) << R[6]
      << std::setw(8) << R[7]
      << std::setw(8) << R[8] << "\n";
    // clang-format on
  }

  void prettyPrint(const Quaternion& q)
  {
    // clang-format off
    std::cout << "Quaternion:\n"
      << std::fixed << std::setprecision(4)
      << " w:" << std::setw(8) << q[0] << "\n"
      << " x:" << std::setw(8) << q[1] << "\n"
      << " y:" << std::setw(8) << q[2] << "\n"
      << " z:" << std::setw(8) << q[3] << "\n";
    // clang-format on
  }
} // namespace euler
