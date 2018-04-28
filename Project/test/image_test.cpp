#include "catch.hpp"

#include "image.hpp"

TEST_CASE("Image", "[Graphics]") {
    Image img(200, 100);

    SECTION("Modify color at centain point") {
        Color red = {1, 0, 0};
        img.color_at(100, 50) = red;
        const Color& result = img.color_at(100, 50);

        REQUIRE(result.r == Approx(1));
        REQUIRE(result.g == Approx(0));
        REQUIRE(result.b == Approx(0));
    }

    SECTION("Bound checking of color_at function") {
        REQUIRE_THROWS_AS(img.color_at(-1, -1), std::out_of_range);
        REQUIRE_THROWS_AS(img.color_at(200, 0), std::out_of_range);
        REQUIRE_THROWS_AS(img.color_at(0, 100), std::out_of_range);
    }
}
