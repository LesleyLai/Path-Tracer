#ifndef HITABLE_HPP
#define HITABLE_HPP

#include <optional>

#include "aabb.hpp"
#include "vector.hpp"

struct Ray;
class Material;

/**
 * @brief Data recorded for a ray-object intersection
 */
struct Hit_record {
  float t{};
  Vec3f point{};  ///< Intersection point
  Vec3f normal{}; ///< Surface normal, need to be construct as a unit vector
  const Material* material{};
};

using Maybe_hit_t = std::optional<Hit_record>;

struct Hitable {
  virtual ~Hitable() = default;

  /**
   * @brief Get the bounding box of an object
   * @return An AABB for objects with bounding_box, nothing otherwise (for
   * example, infinite plane)
   */
  virtual std::optional<AABB> bounding_box() const noexcept = 0;

  /**
   * @brief Ray-object intersection detection
   * @return A optional record of intersection information, nothing if not hit
   */
  virtual Maybe_hit_t intersect_at(const Ray& r, float t_min, float t_max) const
      noexcept = 0;
};

#endif // HITABLE_HPP
