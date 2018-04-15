#ifndef RAY_HPP
#define RAY_HPP

#include <cassert>
#include "vector.hpp"

/**
 * @brief Represent a function of ray F(t)=x+yt where x and y are two vectors
 * that represent origin and direction
 */
class Ray
{
public:
    /**
      * @brief Default construct a ray with origin at <0,0,0> and facing 0 direciton
      */
    constexpr Ray() = default;

    /**
     * @brief Construct a ray by its origin and direction
     * @related Ray
     */
    constexpr Ray(Vec3d a, Vec3d b) : origin_{a}, direction_{b / b.length()} {}

    /**
     * @brief Gets the result point after we put the parameter t into the ray function
     */
    constexpr Vec3d point_at_parameter(double t) const noexcept {
        assert(t >= 0);
        return origin_ + t * direction_;
    }

    constexpr Vec3d origin() const noexcept
    {
        return origin_;
    }

    constexpr void setOrigin(const Vec3d &origin) noexcept
    {
        origin_ = origin;
    }

    constexpr Vec3d direction() const noexcept
    {
        return direction_;
    }

    constexpr void setDirection(const Vec3d &direction) noexcept
    {
        direction_ = direction / direction.length();
    }

private:
    Vec3d origin_ = {0, 0, 0};
    Vec3d direction_ = {1, 0, 0};
};

#endif // RAY_HPP
