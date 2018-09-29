#include "ray.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include <catch2/catch.hpp>

SCENARIO("Creating a Scene", "[scene]")
{
  GIVEN("A scene s")
  {
    Scene s;
    THEN("s contains no objects") { REQUIRE(s.empty()); }
  }
}
