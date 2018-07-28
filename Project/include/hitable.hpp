#ifndef HITABLE_HPP
#define HITABLE_HPP

#include "vector.hpp"
#include <optional>

struct Ray;
class Material;

/**
 * @brief Data recorded for a ray-object intersection
 */
struct Hit_record {
  float t;
  Vec3f point;  ///< Intersection point
  Vec3f normal; ///< Surface normal, need to be construct as a unit vector
  const Material* material;
};

#endif // HITABLE_HPP
