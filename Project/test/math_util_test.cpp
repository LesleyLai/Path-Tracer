#include <algorithm>
#include <catch.hpp>

#include "math_util.hpp"

TEST_CASE("ffminmax", "[Utilities]")
{
  GIVEN("Two float point numbers")
  {
    float a = 1, b = 2;
    SECTION("ffminmax should returns same result as std::minmax")
    {
      const auto [result1, result2] = ffminmax(a, b);
      const auto [expect1, expect2] = std::minmax(a, b);
      REQUIRE(result1 == Approx(expect1));
      REQUIRE(result2 == Approx(expect2));
    }
  }
}
