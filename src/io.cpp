#include <euler/io.h>
#include <iomanip>
#include <algorithm>

std::ostream& operator<<(std::ostream& os, const euler::Quaternion& q)
{
  os << "w: " << q.w() << "\n"
     << "x: " << q.x() << "\n"
     << "y: " << q.y() << "\n"
     << "z: " << q.z();
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
    std::cout << "Rotation Matrix:\n";
    std::cout << std::fixed << std::setprecision(4)
      << std::setw(8) << R(0, 0)
      << std::setw(8) << R(0, 1)
      << std::setw(8) << R(0, 2) << "\n"
      << std::setw(8) << R(1, 0)
      << std::setw(8) << R(1, 1)
      << std::setw(8) << R(1, 2) << "\n"
      << std::setw(8) << R(2, 0)
      << std::setw(8) << R(2, 1)
      << std::setw(8) << R(2, 2) << "\n";
  }

  void prettyPrint(const Quaternion& q)
  {
    std::cout << "Quaternion:\n";
    std::cout << std::fixed << std::setprecision(4)
              << " w: " << std::setw(7) << q.w() << "\n"
              << " x: " << std::setw(7) << q.x() << "\n"
              << " y: " << std::setw(7) << q.y() << "\n"
              << " z: " << std::setw(7) << q.z() << "\n";
  }
}  // namespace euler
