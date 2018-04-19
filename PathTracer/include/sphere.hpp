#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cassert>
#include <optional>

#include "hitable.hpp"
#include "vector.hpp"

struct Sphere : public Hitable
{
    Vec3d center;
    double radius = 1;

    Sphere(Vec3d center, double radius): Hitable{},
        center{center}, radius{radius} {}

    /**
     * Ray-sphere intersection detection
     * @see Hitable::intersect_at
     */
    std::optional<Hit_record> intersect_at(const Ray& r) noexcept override;
};

#endif // SPHERE_HPP
