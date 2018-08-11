/**
 * @file sphere.hpp
 * @brief File for sphere, one of the geometric primetives
 */

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cassert>
#include <optional>

#include "hitable.hpp"
#include "material.hpp"
#include "point.hpp"

struct Sphere : Hitable {
  Point3f center{};
  float radius = 1;
  const Material* const material;

  Sphere(Point3f center, float radius, const Material& mat)
      : center{center}, radius{radius}, material{&mat}
  {
  }

  std::optional<AABB> bounding_box() const noexcept override;

  /**
   * @brief Ray-sphere intersection detection
   * @see Hitable::intersect_at
   */
  Maybe_hit_t intersect_at(const Ray& r, float t_min, float t_max) const
      noexcept override;
};

#endif // SPHERE_HPP
