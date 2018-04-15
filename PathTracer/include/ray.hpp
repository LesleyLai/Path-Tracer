#ifndef RAY_HPP
#define RAY_HPP

#include <cassert>
#include "vector.hpp"

/**
 * @brief Represent a function of ray F(t)=A+Bt where x and y are two vectors
 * that represent origin and direction
 *
 * @warning Ray do not garentee that its direction is a unit vector
 */
struct Ray
{
    Vec3d origin = {0, 0, 0};
    Vec3d direction = {1, 0, 0};

    /**
      * @brief Default construct a ray with origin at <0,0,0> and facing 0 direciton
      */
    constexpr Ray() = default;

    /**
     * @brief Construct a ray by its origin and direction
     * @related Ray
     */
    constexpr Ray(Vec3d a, Vec3d b) : origin{a}, direction{b} {}

    /**
     * @brief Gets the result point after we put the parameter t into the ray function
     */
    constexpr Vec3d point_at_parameter(double t) const noexcept {
        assert(t >= 0);
        return origin + t * direction;
    }
};

#endif // RAY_HPP
