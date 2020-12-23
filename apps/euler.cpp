#include <euler/io.h>
#include <euler/rotations.h>

#include <argagg/argagg.hpp>

#include <cmath>
#include <iomanip>
#include <iostream>

using namespace euler;

int main(int argc, char* argv[]) {
  // Create the parser
  // clang-format off
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
      "Use radians rather than degrees for input angles", 
      0
    },
    {
      "extrinsic", 
      {"-e", "--extrinsic"}, 
      "Use extrinsic rather than intrinsic elemental rotations", 
      0
    },
    {
      "passive", 
      {"-p", "--passive"}, 
      "Specify a passive rather than active rotation", 
      0
    },
    {
      "sequence",
      {"-s", "--sequence"},
      "The rotation sequence (possible values: xyz, xzy, yxz, yzx, zxy, zyx,\n\t"
      "xyx, xzx, yxy, yzy, zxz, zyz; default: zyx)", 
      1
    }
  }};
  // clang-format on

  // Define usage text
  std::ostringstream usage;
  // clang-format off
  usage << "Usage: euler [-r | --radians] [-e | --extrinsic] [-p | --passive]\n"
        << std::setw(57) << std::right
        << "[-s S | --sequence=S] -- ANGLE ANGLE ANGLE\n\n";

  usage << "Calculates rotation matrix and quaternion for given Euler angle sequence.\n"
           "The rotation matrix pre-multiplies vectors in a right-handed coordinate frame.\n"
           "By default the sequence of angles are intepreted to be in degrees and are applied\n"
           "in intrinsic order using the zyx sequence.\n\n";

  usage << "Examples:\n"
           "    euler -- 20 -10 35\n"
           "    euler -ep -- 11.1 23.9 -129.4\n"
           "    euler -e -s yzy -- 41.2 -55.5 -97.8\n"
           "    euler -p -s zxy -- -176.234 -0.231 44.399\n"
           "    euler -rpe -s xzx -- 0.21 1.16 -2.81\n\n";
  // clang-format on

  // Parse the arguments
  argagg::parser_results args;
  try {
    args = arg_parser.parse(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << "Error: Invalid arguments.\n\n" << usage.str() << arg_parser << std::endl;
    return -1;
  }

  // If the help flag was specified, show usage and exit
  if (args["help"]) {
    std::cerr << usage.str() << arg_parser << std::endl;
    return 0;
  }

  // Get radians / degrees
  const bool radians = args["radians"];

  // Get order
  const auto order = args["extrinsic"] ? Order::EXTRINSIC : Order::INTRINSIC;

  // Get active // passive
  const auto direction = args["passive"] ? Direction::PASSIVE : Direction::ACTIVE;

  // Get sequence
  const auto sequence = args["sequence"].as<std::string>("zyx");
  if (!isSequenceValid(sequence)) {
    std::cerr << "Error: Invalid sequence.\n\n" << usage.str() << arg_parser << std::endl;
    return -1;
  }

  // Get angles
  if (args.count() != 3) {
    std::cerr << "Error: Must provide exactly three angles.\n\n"
              << usage.str() << arg_parser << std::endl;
    return -1;
  }
  Angles angles;
  try {
    angles = {std::stod(args.pos[0]), std::stod(args.pos[1]), std::stod(args.pos[2])};
  } catch (const std::invalid_argument&) {
    std::cerr << "Error: Invalid angles, must be three real numbers.\n\n"
              << usage.str() << arg_parser << std::endl;
    return -1;
  }

  // Convert / verify angles
  if (!radians) {
    std::for_each(angles.begin(), angles.end(), [](double& a) { a *= M_PI / 180; });
  }

  // Create rotation matrix and quaternion from arguments
  const RotationMatrix R = toRotationMatrix(sequence, angles, {order, direction});
  const Quaternion q = toQuaternion(R);

  // Display results
  std::cout << "\nRotation Matrix:\n" << R << "\n";
  std::cout << "\nQuaternion:\n" << q << "\n";

  return 0;
}
