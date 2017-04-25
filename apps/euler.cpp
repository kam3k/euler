#include <iostream>
#include <euler/io.h>
#include <euler/rotations.h>

int main()
{
  euler::RotationMatrix R = euler::getRotationMatrix("xyz", {0, 0, M_PI/2}, true, true);
  std::cout << R << "\n";
  euler::Quaternion q = euler::getQuaternion(R);
  std::cout << q << "\n";
  return 0;
}
