#include <euler/io.h>

std::ostream& operator<<(std::ostream& os, const Eigen::Quaterniond& q)
{
  os << "w: " << q.w() << "\n"
     << "x: " << q.x() << "\n"
     << "y: " << q.y() << "\n"
     << "z: " << q.z();
  return os;
}
