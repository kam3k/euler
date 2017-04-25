#include <iostream>
#include <rotation_matrix.h>

int main()
{
  Eigen::Matrix3d R = euler::rotationMatrix("xyz", {0, 0, M_PI/2}, true, true);
  std::cout << R << "\n";
  return 0;
}
