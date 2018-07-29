#include "vector.hpp"

#include <catch.hpp>

/**
 * @brief 3d Axis aligned bounding boxes are used for bounding volume
 * hierarchies
 */
class AABB {
public:
  AABB() = default;

  /**
   * @brief Construction an AABB from its minimal corner to maximum corner
   */
  AABB(Vec3f min, Vec3f max) : min_{min}, max_{max} {}

  Vec3f min() const { return min_; }
  Vec3f max() const { return max_; }

private:
  Vec3f min_ = {};
  Vec3f max_ = {};
};
