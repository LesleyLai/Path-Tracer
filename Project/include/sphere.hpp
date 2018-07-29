#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cassert>
#include <optional>

#include "hitable.hpp"
#include "material.hpp"
#include "vector.hpp"

struct Sphere : Hitable {
  Vec3f center;
  float radius = 1;
  const Material material;

  Sphere(Vec3f center, float radius, Material mat)
      : center{center}, radius{radius}, material{mat}
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
