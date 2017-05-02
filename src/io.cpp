#include <euler/io.h>

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
  bool isSequenceValid(const Sequence& sequence)
  {
    return true;
  }

  bool areAnglesValid(const Angles& angles)
  {
    return false;
  }
}  // namespace euler
