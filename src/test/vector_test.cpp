#include <catch2/catch.hpp>
#include <sstream>

#include "vector.hpp"

TEST_CASE("Vectors", "[math]")
{
  Vec3d v{1, 2, 3};
  Vec3d v2{3, 5, 7};
  const Vec3d sum{4, 7, 10};
  const Vec3d diff{-2, -3, -4};
  const Vec3d two_v{2, 4, 6};
  const Vec3d half_v{0.5, 1, 1.5};

  SECTION("Construct Vector from a smaller vector and a scalar")
  {
    Vec2d v3{3, 5};
    REQUIRE(Vec3d{v3, 7} == v2);
    REQUIRE(Vec4d{v2, 9} == Vec4d{3, 5, 7, 9});
  }

  SECTION("Array-style indexing for Vectors") { REQUIRE(v[2] == Approx(3)); }

  SECTION("Print Vector")
  {
    std::stringstream ss;
    ss << v;
    REQUIRE(ss.str() == "vec(1, 2, 3)");
  }

  SECTION("Comparison of Vector")
  {
    REQUIRE(v == Vec3d{1, 2, 3});
    REQUIRE(v != Vec3d{2, 2, 3});
  }

  SECTION("Unary operations of Vector")
  {
    SECTION("+=")
    {
      v += v2;
      REQUIRE(v == sum);
    }

    SECTION("+=")
    {
      v -= v2;
      REQUIRE(v == diff);
    }

    SECTION("*=")
    {
      v *= 2.;
      REQUIRE(v == two_v);
    }

    SECTION("/=")
    {
      v /= 2.;
      REQUIRE(v == half_v);
    }

    SECTION("Negation") { REQUIRE(-v == Vec3d{-1, -2, -3}); }
  }

  SECTION("Binary operations of Vector")
  {
    SECTION("+") { REQUIRE(v + v2 == sum); }

    SECTION("-") { REQUIRE(v - v2 == diff); }

    SECTION("*")
    {
      REQUIRE(v * 2. == two_v);
      REQUIRE(2. * v == two_v);
    }

    SECTION("/") { REQUIRE(v / 2. == half_v); }

    SECTION("dot product") { REQUIRE(dot(v, v2) == Approx(34)); }

    SECTION("cross product") { REQUIRE(cross(v, v2) == Vec3d{-1, 2, -1}); }
  }

  SECTION("Length of the Vector")
  {

    REQUIRE(v.length_square() == Approx(14));
    REQUIRE(v.length() == Approx(std::sqrt(14)));
  }

  SECTION("Normalize the vector")
  {
    const auto u = normalize(v);
    const auto length = v.length();
    REQUIRE(u.x == Approx(v.x / length));
    REQUIRE(u.y == Approx(v.y / length));
    REQUIRE(u.z == Approx(v.z / length));
  }
}
