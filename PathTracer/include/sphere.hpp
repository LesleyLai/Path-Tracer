#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cassert>
#include <optional>

#include "vector.hpp"
#include "ray.hpp"

struct Sphere
{
    Vec3d center;
    double radius = 1;

    /**
     * @brief Ray-sphere intersection detection
     * @param r The ray to check intersection
     * @return std::nullopt if the ray do not intersect with the sphere,
     * a number t if the ray intersects the sphere at point (a + bt)
     */
    std::optional<double> intersect_at(const Ray& r) noexcept;
};

#endif // SPHERE_HPP
