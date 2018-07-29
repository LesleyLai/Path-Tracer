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
  float t{};
  Vec3f point;  ///< Intersection point
  Vec3f normal; ///< Surface normal, need to be construct as a unit vector
  const Material* material{};
};

using Maybe_hit_t = std::optional<Hit_record>;

struct Hitable {
  Hitable() = default;
  virtual ~Hitable() = default;
  Hitable(const Hitable&) = default;
  Hitable& operator=(const Hitable&) = default;
  Hitable(Hitable&&) = default;
  Hitable& operator=(Hitable&&) = default;

  virtual Maybe_hit_t intersect_at(const Ray& r, float t_min, float t_max) const
      noexcept = 0;
};

#endif // HITABLE_HPP
