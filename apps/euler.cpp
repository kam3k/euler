#include <iostream>
#include <argagg/argagg.hpp>
#include <euler/io.h>
#include <euler/rotations.h>

int main(int argc, char* argv[])
{
  // Create the parser
  argagg::parser arg_parser {{
    {
      "help", 
      {"-h", "--help"}, 
      "Print help and exit", 
      0
    },
    {
      "radians", 
      {"-r", "--radians"}, 
      "Use radians instead of degrees for input angles (default: false)", 
      0
    },
    {
      "intrinsic", 
      {"-i", "--intrinsic"}, 
      "Use intrinsic elemental rotations (default: true)", 
      0
    },
    {
      "extrinsic", 
      {"-e", "--extrinsic"}, 
      "Use extrinsic elemental rotations (default: false)", 
      0
    },
    {
      "active", 
      {"-a", "--active"}, 
      "Specify an active rotation (default: true)", 
      0
    },
    {
      "passive", 
      {"-p", "--passive"}, 
      "Specify a passive rotation (default: false)", 
      0
    },
    {
      "sequence",
      {"-s", "--sequence"},
      "The rotation sequence (possible values: xyz, xzy, yxz, yzx, zxy, zyx,\n\t"
      "xyx, xzx, yxy, yzy, zxz, zyz; default: xyz)", 
      1
    }
  }};

  // Define usage text
  std::ostringstream usage;
  usage << "Usage: euler "
        << "[-r | --radians] [-i | --intrinsic | -e | --extrinsic]\n\t"
           "[-a | --active | -p | --passive] [-s S | --sequence=S]\n\tangle "
           "angle angle\n\n"
           "Examples:\n\teuler 20 -10 35\n\teuler -ep 11.1 23.9 "
           "-129.4\n\teuler -ea -s yzy 41.2 -55.5 -97.8\n\teuler -p -s zxy "
           "-176.234 -0.231 44.399\n\teuler -rpi -s xzx 0.21 1.16 -2.81\n\n";

  // Parse the arguments
  argagg::parser_results args;
  try
  {
    args = arg_parser.parse(argc, argv);
  }
  catch (const std::exception& e)
  {
    std::cerr << usage.str() << arg_parser << std::endl
              << "Encountered exception while parsing arguments: " << e.what()
              << std::endl;
    return -1;
  }

	// If the help flag was specified, show usage and exit
  if (args["help"])
  {
    std::cerr << usage.str() << arg_parser << std::endl;
    return 0;
  }

  // Create rotation matrix and quaternion from arguments
  /* const euler::RotationMatrix R = */
  /*     euler::getRotationMatrix(sequence, angles, convention); */
  /* const euler::Quaternion q = euler::getQuaternion(R); */

  // Display results

  return 0;
}
