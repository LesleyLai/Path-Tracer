#include "sphere.hpp"
#include "ray.hpp"
#include <catch.hpp>

#include <iostream>

TEST_CASE("Ray-Sphere intersection", "[geometry]") {
    Ray ray({0, 0, 0}, {0, 0, 1});

    SECTION("intersect_at returns nullopt if sphere does not intersect the ray") {
        Sphere sphere{{0, 2, 0}, 1};
        REQUIRE_FALSE(sphere.intersect_at(ray));
    }

    SECTION("intersect_at returns nullopt if intersections happened behind the ray") {
        Sphere sphere{{0, 0, -2}, 1};
        REQUIRE_FALSE(sphere.intersect_at(ray));
    }

    SECTION("intersect_at returns smaller t when intersect with the sphere at two points") {
        Sphere sphere{{0, 0, 2}, 1};
        const auto result = sphere.intersect_at(ray);
        REQUIRE(result);
        REQUIRE(result->t == Approx(1));
    }

    SECTION("intersect_at returns positive t if one of the intersection point happened behind the ray") {
        Sphere sphere{{0, 0, 0}, 2};
        const auto result = sphere.intersect_at(ray);
        REQUIRE(result);
        REQUIRE(result->t == Approx(2));
    }
}
