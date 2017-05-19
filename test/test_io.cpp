#include <catch/catch.hpp>
#include <euler/io.h>
#include <cmath>

using namespace euler;

TEST_CASE("Sequence validity")
{
  SECTION("No sequence given")
  {
    CHECK(isSequenceValid("") == false);
  }

  SECTION("Valid sequence")
  {
    std::array<std::string, 12> sequences = {"xyz", "xzy", "yxz", "yzx",
                                             "zxy", "zyx", "xyx", "xzx",
                                             "yxy", "yzy", "zxz", "zyz"};
    for (const auto& seq : sequences)
    {
      CHECK(isSequenceValid(seq) == true);
    }
  }

  SECTION("Invalid sequence")
  {
    std::vector<std::string> sequences = {"xxz", "xyy", "zxx",  "yyz", "xxx",
                                          "yyy", "zzz", "zzx",  "zzy", "yxx",
                                          "xxy", "123", "1.23", "54",  "sd9a"};
    for (const auto& seq : sequences)
    {
      CHECK(isSequenceValid(seq) == false);
    }
  }
}
