#include <catch2/catch.hpp>

#include "color.hpp"

TEST_CASE("Colors", "[Color]")
{
  Color white(1, 1, 1);
  Color black(0, 0, 0);
  Color red(1, 0, 0);
  Color blue(0, 0, 1);

  SECTION("Construct color do not check overflow")
  {
    const Color tmp(-1, 0, 2);
    REQUIRE(tmp.r == Approx(-1));
    REQUIRE(tmp.g == Approx(0));
    REQUIRE(tmp.b == Approx(2));
  }

  SECTION("Addition of RGB float colors")
  {
    const auto tmp = red + blue;
    REQUIRE(tmp.r == Approx(1));
    REQUIRE(tmp.g == Approx(0));
    REQUIRE(tmp.b == Approx(1));
  }

  SECTION("Subtraction of RGB float colors")
  {
    const auto tmp = white - blue;
    REQUIRE(tmp.r == Approx(1));
    REQUIRE(tmp.g == Approx(1));
    REQUIRE(tmp.b == Approx(0));
  }

  SECTION("Scalar multiplication")
  {
    const auto tmp = white * .42f;
    const auto tmp2 = .33f * white;

    REQUIRE(tmp.r == Approx(.42));
    REQUIRE(tmp.g == Approx(.42));
    REQUIRE(tmp.b == Approx(.42));

    REQUIRE(tmp2.r == Approx(.33));
    REQUIRE(tmp2.g == Approx(.33));
    REQUIRE(tmp2.b == Approx(.33));
  }

  SECTION("Scalar inplace division")
  {
    white /= 2;

    REQUIRE(white.r == Approx(.5));
    REQUIRE(white.g == Approx(.5));
    REQUIRE(white.b == Approx(.5));
  }

  SECTION("Clamp overflowed colors")
  {
    white += Color(.1f, .1f, .1f);
    white.clamp();
    REQUIRE(white.r == Approx(1));
    REQUIRE(white.g == Approx(1));
    REQUIRE(white.b == Approx(1));

    black -= Color(.5f, .5f, .5f);
    black.clamp();
    REQUIRE(black.r == Approx(0));
    REQUIRE(black.g == Approx(0));
    REQUIRE(black.b == Approx(0));
  }
}
