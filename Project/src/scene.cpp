#include <limits>

#include "scene.hpp"

/**
 * @param r The ray to check intersection
 * @return std::nullopt if the ray do not intersect with the sphere,
 * a Hit_record struct if the ray intersects the sphere
 */

Maybe_hit_t Scene::intersect_at(const Ray& r) const noexcept
{
  assert(aggregate_ != nullptr);
  return aggregate_->intersect_at(r, 0.00001f,
                                  std::numeric_limits<float>::infinity());
}
