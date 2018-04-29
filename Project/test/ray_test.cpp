#include "catch.hpp"

#include "ray.hpp"

TEST_CASE("Ray", "[geometry]") {
    const Vec3f origin = {1, 1, 1};
    const Vec3f direction = {0, 0, 1};

    SECTION("Default construct a ray at origin") {
        Ray default_ray;
        REQUIRE(default_ray.origin == Vec3f{0,0,0});
    }

    SECTION("Construct a ray with input") {
        Ray ray {origin, direction};

        REQUIRE(ray.origin == origin);
        REQUIRE(ray.direction == direction);
    }

    SECTION("Gets correct point at parameter t from the ray function") {
        Ray ray {origin, direction};
        const auto expect_dest = origin + 3.f * direction;
        const auto dest = ray.point_at_parameter(3);

        REQUIRE(expect_dest.x == Approx(dest.x));
        REQUIRE(expect_dest.y == Approx(dest.y));
        REQUIRE(expect_dest.z == Approx(dest.z));
    }
}








