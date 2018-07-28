#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cassert>
#include <optional>

#include "hitable.hpp"
#include "material.hpp"
#include "vector.hpp"

struct Sphere {
  Vec3f center;
  float radius = 1;
  const Material material;

  Sphere(Vec3f center, float radius, Material mat)
      : center{center}, radius{radius}, material{mat}
  {
  }

  /**
   * Ray-sphere intersection detection
   * @see Hitable::intersect_at
   */
  std::optional<Hit_record> intersect_at(const Ray& r, float t_min,
                                         float t_max) const noexcept;
};

#endif // SPHERE_HPP
