#include <catch/catch.hpp>
#include <rotations.h>
#include <cmath>

using namespace euler;

TEST_CASE("Identity")
{
  RotationMatrix R_expect = RotationMatrix::Identity(3, 3);
  RotationMatrix R_actual = getRotationMatrix("xyz", {0, 0, 0}, false, false);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("xyz", {0, 0, 0}, true, false);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("xyz", {0, 0, 0}, false, true);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("xyz", {0, 0, 0}, true, true);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("yzy", {0, 0, 0}, false, false);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("yzy", {0, 0, 0}, true, false);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("yzy", {0, 0, 0}, false, true);
  CHECK(R_actual.isApprox(R_expect));
  R_actual = getRotationMatrix("yzy", {0, 0, 0}, true, true);
  CHECK(R_actual.isApprox(R_expect));
}

TEST_CASE("Rotation about principal axes")
{
  const auto theta = M_PI/4.3;
  const auto s = std::sin(theta);
  const auto c = std::cos(theta);

  SECTION("Rotation about x-axis")
  {
    SECTION("Active")
    {
      RotationMatrix R_expect_active;
      R_expect_active << 1, 0,  0,
                         0, c, -s,
                         0, s,  c;
      RotationMatrix R_actual_active =
          getRotationMatrix("xyz", {theta, 0, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("yxz", {0, theta, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("zyx", {0, 0, theta}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
    }

    SECTION("Passive")
    {
      RotationMatrix R_expect_passive;
      R_expect_passive << 1,  0,  0,
                          0,  c,  s,
                          0, -s,  c;
      RotationMatrix R_actual_passive =
          getRotationMatrix("xyz", {theta, 0, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("yxz", {0, theta, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("zyx", {0, 0, theta}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
    }
  }

  SECTION("Rotation about y-axis")
  {
    SECTION("Active")
    {
      RotationMatrix R_expect_active;
      R_expect_active << c, 0,  s,
                         0, 1,  0,
                        -s, 0,  c;
      RotationMatrix R_actual_active =
          getRotationMatrix("yzx", {theta, 0, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("xyz", {0, theta, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("zxy", {0, 0, theta}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
    }

    SECTION("Passive")
    {
      RotationMatrix R_expect_passive;
      R_expect_passive << c,  0, -s,
                          0,  1,  0,
                          s,  0,  c;
      RotationMatrix R_actual_passive =
          getRotationMatrix("yzx", {theta, 0, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("xyz", {0, theta, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("zxy", {0, 0, theta}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
    }
  }

  SECTION("Rotation about z-axis")
  {
    SECTION("Active")
    {
      RotationMatrix R_expect_active;
      R_expect_active << c, -s,  0,
                         s,  c,  0,
                         0,  0,  1;
      RotationMatrix R_actual_active =
          getRotationMatrix("zyx", {theta, 0, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("xzy", {0, theta, 0}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
      R_actual_active = getRotationMatrix("yxz", {0, 0, theta}, false, true);
      CHECK(R_actual_active.isApprox(R_expect_active));
    }

    SECTION("Passive")
    {
      RotationMatrix R_expect_passive;
      R_expect_passive << c,  s,  0,
                         -s,  c,  0,
                          0,  0,  1;
      RotationMatrix R_actual_passive =
          getRotationMatrix("zyx", {theta, 0, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("xzy", {0, theta, 0}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
      R_actual_passive = getRotationMatrix("yxz", {0, 0, theta}, false, false);
      CHECK(R_actual_passive.isApprox(R_expect_passive));
    }
  }
}
