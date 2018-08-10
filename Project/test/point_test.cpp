#include <catch.hpp>

#include "point.hpp"

TEST_CASE("Point", "[math]")
{
  Point3d p{1, 2, 3};
  Point3d p2{2, 3, 4};
  Vec3d v{1, 1, 1};

  SECTION("Array-style indexing for Point")
  {
    REQUIRE(p[2] == Approx(3));
    ++p[2];
    REQUIRE(p[2] == Approx(4));
  }

  SECTION("Comparison of Point")
  {
    REQUIRE(p == p);
    REQUIRE(p != p2);
  }

  SECTION("Unary operations for Point")
  {
    SECTION("Point += Vector")
    {
      p += v;
      REQUIRE(p == p2);
    }

    SECTION("Point -= Vector")
    {
      p -= v;
      REQUIRE(p == Point3d{0, 1, 2});
    }
  }

  SECTION("Binary operations for Point")
  {
    SECTION("Point + Vector = Point") { REQUIRE(p + v == p2); }
    SECTION("Point - Vector = Point") { REQUIRE(p2 - v == p); }
    SECTION("Vector + Point = Point") { REQUIRE(v + p == p2); }
    SECTION("Point - Point = Vector") { REQUIRE(p2 - p == v); }
  }
}
