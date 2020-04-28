#include <catch/catch.hpp>

#include <euler/io.h>
#include <euler/rotations.h>

#include <cmath>
#include <iostream>

using namespace euler;

static const double TOLERANCE = 1e-6;

template <std::size_t SIZE>
bool approxEq(const std::array<double, SIZE>& lhs,
              const std::array<double, SIZE>& rhs)
{
  for (std::size_t i = 0; i < SIZE; ++i)
  {
    if (std::abs(lhs[i] - rhs[i]) > TOLERANCE)
    {
      return false;
    }
  }
  return true;
}

using Vector = std::array<double, 3>;

Vector operator*(const RotationMatrix& R, const Vector& v)
{
  return {R[0] * v[0] + R[1] * v[1] + R[2] * v[2],
          R[3] * v[0] + R[4] * v[1] + R[5] * v[2],
          R[6] * v[0] + R[7] * v[1] + R[8] * v[2]};
}

TEST_CASE("Identity")
{
  RotationMatrix R_expect = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  RotationMatrix R_actual = toRotationMatrix(
      "xyz", {0, 0, 0}, {Order::INTRINSIC, Direction::PASSIVE});
  CHECK(approxEq(R_actual, R_expect));
  R_actual = toRotationMatrix("xyz", {0, 0, 0},
                              {Order::EXTRINSIC, Direction::PASSIVE});
  CHECK(approxEq(R_actual, R_expect));
  R_actual =
      toRotationMatrix("xyz", {0, 0, 0}, {Order::INTRINSIC, Direction::ACTIVE});
  CHECK(approxEq(R_actual, R_expect));
  R_actual =
      toRotationMatrix("xyz", {0, 0, 0}, {Order::EXTRINSIC, Direction::ACTIVE});
  CHECK(approxEq(R_actual, R_expect));
  R_actual = toRotationMatrix("yzy", {0, 0, 0},
                              {Order::INTRINSIC, Direction::PASSIVE});
  CHECK(approxEq(R_actual, R_expect));
  R_actual = toRotationMatrix("yzy", {0, 0, 0},
                              {Order::EXTRINSIC, Direction::PASSIVE});
  CHECK(approxEq(R_actual, R_expect));
  R_actual =
      toRotationMatrix("yzy", {0, 0, 0}, {Order::INTRINSIC, Direction::ACTIVE});
  CHECK(approxEq(R_actual, R_expect));
  R_actual =
      toRotationMatrix("yzy", {0, 0, 0}, {Order::EXTRINSIC, Direction::ACTIVE});
  CHECK(approxEq(R_actual, R_expect));
}

TEST_CASE("Rotations about principal axes")
{
  const auto theta = M_PI / 4.3;
  const auto s = std::sin(theta);
  const auto c = std::cos(theta);

  SECTION("Rotation about x-axis")
  {
    SECTION("Active")
    {
      RotationMatrix R_expect_active = {1.0, 0.0, 0.0, 0.0, c, -s, 0.0, s, c};
      RotationMatrix R_actual_active = toRotationMatrix(
          "xyz", {theta, 0, 0}, {Order::INTRINSIC, Direction::ACTIVE});
      CHECK(approxEq(R_actual_active, R_expect_active));
      R_actual_active = toRotationMatrix("yxz", {0, theta, 0},
                                         {Order::INTRINSIC, Direction::ACTIVE});
      CHECK(approxEq(R_actual_active, R_expect_active));
      R_actual_active = toRotationMatrix("zyx", {0, 0, theta},
                                         {Order::INTRINSIC, Direction::ACTIVE});
      CHECK(approxEq(R_actual_active, R_expect_active));
    }

    SECTION("Passive")
    {
      RotationMatrix R_expect_passive = {1.0, 0.0, 0.0, 0.0, c, s, 0.0, -s, c};
      RotationMatrix R_actual_passive = toRotationMatrix(
          "xyz", {theta, 0, 0}, {Order::INTRINSIC, Direction::PASSIVE});
      CHECK(approxEq(R_actual_passive, R_expect_passive));
      R_actual_passive = toRotationMatrix(
          "yxz", {0, theta, 0}, {Order::INTRINSIC, Direction::PASSIVE});
      CHECK(approxEq(R_actual_passive, R_expect_passive));
      R_actual_passive = toRotationMatrix(
          "zyx", {0, 0, theta}, {Order::INTRINSIC, Direction::PASSIVE});
      CHECK(approxEq(R_actual_passive, R_expect_passive));
    }
  }

  SECTION("Rotation about y-axis")
  {
    SECTION("Active")
    {
      RotationMatrix R_expect_active = {c, 0.0, s, 0.0, 1.0, 0.0, -s, 0.0, c};
      RotationMatrix R_actual_active = toRotationMatrix(
          "yzx", {theta, 0, 0}, {Order::INTRINSIC, Direction::ACTIVE});
      CHECK(approxEq(R_actual_active, R_expect_active));
      R_actual_active = toRotationMatrix("xyz", {0, theta, 0},
                                         {Order::INTRINSIC, Direction::ACTIVE});
      CHECK(approxEq(R_actual_active, R_expect_active));
      R_actual_active = toRotationMatrix("zxy", {0, 0, theta},
                                         {Order::INTRINSIC, Direction::ACTIVE});
      CHECK(approxEq(R_actual_active, R_expect_active));
    }

    SECTION("Passive")
    {
      RotationMatrix R_expect_passive = {c, 0.0, -s, 0.0, 1.0, 0.0, s, 0.0, c};
      RotationMatrix R_actual_passive = toRotationMatrix(
          "yzx", {theta, 0, 0}, {Order::INTRINSIC, Direction::PASSIVE});
      CHECK(approxEq(R_actual_passive, R_expect_passive));
      R_actual_passive = toRotationMatrix(
          "xyz", {0, theta, 0}, {Order::INTRINSIC, Direction::PASSIVE});
      CHECK(approxEq(R_actual_passive, R_expect_passive));
      R_actual_passive = toRotationMatrix(
          "zxy", {0, 0, theta}, {Order::INTRINSIC, Direction::PASSIVE});
      CHECK(approxEq(R_actual_passive, R_expect_passive));
    }
  }

  SECTION("Rotation about z-axis")
  {
    SECTION("Active")
    {
      RotationMatrix R_expect_active = {c, -s, 0.0, s, c, 0.0, 0.0, 0.0, 1.0};
      RotationMatrix R_actual_active = toRotationMatrix(
          "zyx", {theta, 0, 0}, {Order::INTRINSIC, Direction::ACTIVE});
      CHECK(approxEq(R_actual_active, R_expect_active));
      R_actual_active = toRotationMatrix("xzy", {0, theta, 0},
                                         {Order::INTRINSIC, Direction::ACTIVE});
      CHECK(approxEq(R_actual_active, R_expect_active));
      R_actual_active = toRotationMatrix("yxz", {0, 0, theta},
                                         {Order::INTRINSIC, Direction::ACTIVE});
      CHECK(approxEq(R_actual_active, R_expect_active));
    }

    SECTION("Passive")
    {
      RotationMatrix R_expect_passive = {c, s, 0.0, -s, c, 0.0, 0.0, 0.0, 1.0};
      RotationMatrix R_actual_passive = toRotationMatrix(
          "zyx", {theta, 0, 0}, {Order::INTRINSIC, Direction::PASSIVE});
      CHECK(approxEq(R_actual_passive, R_expect_passive));
      R_actual_passive = toRotationMatrix(
          "xzy", {0, theta, 0}, {Order::INTRINSIC, Direction::PASSIVE});
      CHECK(approxEq(R_actual_passive, R_expect_passive));
      R_actual_passive = toRotationMatrix(
          "yxz", {0, 0, theta}, {Order::INTRINSIC, Direction::PASSIVE});
      CHECK(approxEq(R_actual_passive, R_expect_passive));
    }
  }
}

TEST_CASE("Rotations of 90 degrees about each axis")
{
  std::array<double, 3> angles = {M_PI / 2, M_PI / 2, M_PI / 2};
  Vector a = {1.0, 0.0, 0.0};
  Vector b_expect;
  Vector b_actual;

  SECTION("Intrinsic")
  {
    SECTION("xyz")
    {
      const auto sequence = "xyz";

      SECTION("Active")
      {
        b_expect = {0, 0, 1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, 0, 1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("yzx")
    {
      const auto sequence = "yzx";

      SECTION("Active")
      {
        b_expect = {0, 1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, 1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("zyx")
    {
      const auto sequence = "zyx";

      SECTION("Active")
      {
        b_expect = {0, 0, -1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, 0, 1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("xzy")
    {
      const auto sequence = "xzy";

      SECTION("Active")
      {
        b_expect = {0, 1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, -1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("xyx")
    {
      const auto sequence = "xyx";

      SECTION("Active")
      {
        b_expect = {0, 1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, 1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("zxz")
    {
      const auto sequence = "zxz";

      SECTION("Active")
      {
        b_expect = {0, 0, 1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, 0, 1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("yzy")
    {
      const auto sequence = "yzy";

      SECTION("Active")
      {
        b_expect = {-1, 0, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {-1, 0, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::INTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }
  }

  SECTION("Extrinsic")
  {
    SECTION("xyz")
    {
      const auto sequence = "xyz";

      SECTION("Active")
      {
        b_expect = {0, 0, -1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, 0, 1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("yzx")
    {
      const auto sequence = "yzx";

      SECTION("Active")
      {
        b_expect = {0, 1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, -1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("zyx")
    {
      const auto sequence = "zyx";

      SECTION("Active")
      {
        b_expect = {0, 0, 1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, 0, 1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("xzy")
    {
      const auto sequence = "xzy";

      SECTION("Active")
      {
        b_expect = {0, 1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, 1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("xyx")
    {
      const auto sequence = "xyx";

      SECTION("Active")
      {
        b_expect = {0, 1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, 1, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("zxz")
    {
      const auto sequence = "zxz";

      SECTION("Active")
      {
        b_expect = {0, 0, 1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {0, 0, 1};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }

    SECTION("yzy")
    {
      const auto sequence = "yzy";

      SECTION("Active")
      {
        b_expect = {-1, 0, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::ACTIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }

      SECTION("Passive")
      {
        b_expect = {-1, 0, 0};
        b_actual = toRotationMatrix(sequence, angles,
                                    {Order::EXTRINSIC, Direction::PASSIVE}) *
                   a;
        CHECK(approxEq(b_actual, b_expect));
      }
    }
  }
}

TEST_CASE("General rotations")
{
  SECTION("Intrinsic")
  {
    std::array<double, 3> angles = {11 * M_PI / 180, -38 * M_PI / 180,
                                    4 * M_PI / 180};

    RotationMatrix R_expect;
    // clang-format off
    R_expect = {0.7860912, -0.0549689,  -0.6156615,
               -0.0487127,  0.9874306,  -0.1503595,
                0.616188,   0.1481869,   0.7735327};
    // clang-format on

    RotationMatrix R_actual =
        toRotationMatrix("xyz", angles, {Order::INTRINSIC, Direction::ACTIVE});
    CHECK(approxEq(R_actual, R_expect));

    // Order reversed, but extrinsic should give same solution
    R_actual = toRotationMatrix("zyx", {angles[2], angles[1], angles[0]},
                                {Order::EXTRINSIC, Direction::ACTIVE});
    CHECK(approxEq(R_actual, R_expect));

    // Transpose should give passive solution
    R_expect = transpose(R_expect);
    R_actual =
        toRotationMatrix("xyz", angles, {Order::INTRINSIC, Direction::PASSIVE});
    CHECK(approxEq(R_actual, R_expect));
  }

  SECTION("Extrinsic")
  {
    std::array<double, 3> angles = {11 * M_PI / 180, -38 * M_PI / 180,
                                    4 * M_PI / 180};

    RotationMatrix R_expect;
    // clang-format off
    R_expect = {0.786091,  -0.185662,  -0.589568,
                0.0549689,  0.971041,  -0.232502,
                0.615661,   0.15036,    0.773533};
    // clang-format on

    RotationMatrix R_actual =
        toRotationMatrix("xyz", angles, {Order::EXTRINSIC, Direction::ACTIVE});
    CHECK(approxEq(R_actual, R_expect));

    // Order reversed, but intrinsic should give same solution
    R_actual = toRotationMatrix("zyx", {angles[2], angles[1], angles[0]},
                                {Order::INTRINSIC, Direction::ACTIVE});
    CHECK(approxEq(R_actual, R_expect));

    // Transpose should give passive solution
    R_expect = transpose(R_expect);
    R_actual =
        toRotationMatrix("xyz", angles, {Order::EXTRINSIC, Direction::PASSIVE});
    CHECK(approxEq(R_actual, R_expect));
  }
}

TEST_CASE("Quaternions")
{
  // Just ensure that conversion from rotation matrices to unit quaternions is
  // correct

  // Identity
  RotationMatrix R = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  Quaternion q_expect = {1.0, 0.0, 0.0, 0.0};
  auto q_actual = toQuaternion(R);
  CHECK(approxEq(q_actual, q_expect));

  // Random case verified with converter at
  // https://www.andre-gaschler.com/rotationconverter/
  R = {0.9590657,  0.2713668,  0.0809514, -0.1991297, 0.8495061,
       -0.4885557, -0.2013465, 0.4524372, 0.8687693};
  q_expect = {0.9588197, 0.2453519, 0.0736056, -0.1226759};
  q_actual = toQuaternion(R);
  CHECK(approxEq(q_actual, q_expect));
}
