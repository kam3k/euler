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
      "Use intrinsic elemental rotations (incompatible with -e; default: true)", 
      0
    },
    {
      "extrinsic", 
      {"-e", "--extrinsic"}, 
      "Use extrinsic elemental rotations (incompatible with -i; default: false)", 
      0
    },
    {
      "active", 
      {"-a", "--active"}, 
      "Specify an active rotation (incompatible with -p; default: true)", 
      0
    },
    {
      "passive", 
      {"-p", "--passive"}, 
      "Specify a passive rotation (incompatible with -a; default: false)", 
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
           "[-a | --active | -p | --passive] [-s S | --sequence=S]\n\t-- ANGLE "
           "ANGLE ANGLE\n\n"
           "Calculates rotation matrix and quaternion for given Euler angle sequence.\n\n"
           "Examples:\n\teuler -- 20 -10 35\n\teuler -ep -- 11.1 23.9 "
           "-129.4\n\teuler -ea -s yzy -- 41.2 -55.5 -97.8\n\teuler -p -s zxy "
           "-- -176.234 -0.231 44.399\n\teuler -rpi -s xzx -- 0.21 1.16 -2.81\n\n";

  // Parse the arguments
  argagg::parser_results args;
  try
  {
    args = arg_parser.parse(argc, argv);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: Invalid inputs.\n\n" << usage.str() << arg_parser << std::endl;
    return -1;
  }

  // If the help flag was specified, show usage and exit
  if (args["help"])
  {
    std::cerr << usage.str() << arg_parser << std::endl;
    return 0;
  }

  // Get radians / degrees
  bool radians = args["radians"];

  // Get intrinsic / extrinsic
  euler::Order order =
      args["extrinsic"] ? euler::Order::EXTRINSIC : euler::Order::INTRINSIC;

  // Get active // passive
  euler::Direction direction =
      args["passive"] ? euler::Direction::PASSIVE : euler::Direction::ACTIVE;

  // Get sequence
  const std::string sequence = args["sequence"].as<std::string>("xyz");
  if (!euler::isSequenceValid(sequence))
  {
    std::cerr << "Invalid sequence.\n" << usage.str() << arg_parser << std::endl;
    return -1;
  }

  // Get angles
  if (args.count() != 3)
  {
    std::cerr << "Error: Must provide exactly three angles.\n\n"
              << usage.str() << arg_parser << std::endl;
    return -1;
  }
  euler::Angles angles = {std::stod(args.pos[0]), std::stod(args.pos[1]),
                          std::stod(args.pos[2])};

  // Convert / verify angles
  if (!radians)
  {
    std::for_each(angles.begin(), angles.end(),
                  [](double& a) { a *= M_PI / 180; });
  }

  // Create rotation matrix and quaternion from arguments
  const euler::RotationMatrix R =
      euler::getRotationMatrix(sequence, angles, {order, direction});
  const euler::Quaternion q = euler::getQuaternion(R);

  // Display results
  std::cout << std::endl;
  euler::prettyPrint(R);
  std::cout << std::endl;
  euler::prettyPrint(q);

  return 0;
}
