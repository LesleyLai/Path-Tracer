#include <catch2/catch.hpp>

#include "onb.hpp"

TEST_CASE("ONB", "[math]")
{
  using namespace Catch::literals;

  GIVEN("Default constructed ONB")
  {
    ONB<float> onb;
    THEN("forms the standard bases")
    {
      REQUIRE(onb.u() == Vec3f{1, 0, 0});
      REQUIRE(onb.v() == Vec3f{0, 1, 0});
      REQUIRE(onb.w() == Vec3f{0, 0, 1});
    }

    WHEN(
        "transfer point (3, -2, 7) of local coordinate to the world coordinate")
    {
      THEN("will get point (3, -2, 7)")
      {
        REQUIRE(onb.to_world(Point3f{3, -2, 7}) == Point3f{3, -2, 7});
      }
    }

    WHEN("transfer vector (3, -2, 7) of local coordinate the world coordinate")
    {
      THEN("will get vector (3, -2, 7)")
      {
        REQUIRE(onb.to_world(Vec3f{3, -2, 7}) == Vec3f{3, -2, 7});
      }
    }
  }

  GIVEN("A vector w=(2, 2, 1)")
  {
    const Vec3f w{2, 2, 1};
    WHEN("Constructing an ONB from this vector")
    {
      const auto onb = ONB<float>::from_w(w);
      THEN("The w component of the ONB is normalize(w)")
      {
        const auto w_unit = normalize(w);
        REQUIRE(w_unit.x == Approx(onb.w().x));
        REQUIRE(w_unit.y == Approx(onb.w().y));
        REQUIRE(w_unit.z == Approx(onb.w().z));
      }

      THEN("The u and v component of the ONB are unit vectors")
      {
        REQUIRE(onb.u().length_square() == 1_a);
        REQUIRE(onb.v().length_square() == 1_a);
      }

      THEN("The components of ONB are orthogonal to each other")
      {
        REQUIRE(dot(onb.v(), onb.w()) == (0_a).margin(1e-7));
        REQUIRE(dot(onb.u(), onb.v()) == (0_a).margin(1e-7));
        REQUIRE(dot(onb.u(), onb.w()) == (0_a).margin(1e-7));
      }
    }
  }
}
