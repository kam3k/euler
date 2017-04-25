#ifndef EULER_IO_H
#define EULER_IO_H

#include <iostream>
#include <Eigen/Geometry>

std::ostream& operator<<(std::ostream& os, const Eigen::Quaterniond& q);

namespace euler
{
} // namespace euler

#endif
