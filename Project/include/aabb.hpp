#ifndef AABB_HPP
#define AABB_HPP

#include <algorithm>
#include <cassert>
#include <ostream>

#include "point.hpp"
#include "ray.hpp"

/**
 * @brief 3D Axis aligned bounding boxes are used for bounding volume
 * hierarchies
 */
class AABB {
public:
  constexpr AABB() noexcept = default;

  /**
   * @brief Construction an AABB from its minimal corner to maximum corner
   */
  constexpr AABB(Point3f min, Point3f max) noexcept : min_{min}, max_{max}
  {
    assert(min.x <= max.x);
    assert(min.y <= max.y);
    assert(min.z <= max.z);
  }

  constexpr Point3f min() const { return min_; }
  constexpr Point3f max() const { return max_; }

  /**
   * @brief Whether the ray r hit AABB or not
   */
  constexpr bool hit(const Ray& r, float t_min, float t_max) const
  {
    constexpr int num_dim = 3;
    // Credit: Andrew Kensler at Pixar adapt this version of AABB hit method
    // Shirley, Peter. Ray Tracing: the Next Week
    for (int a = 0; a < num_dim; ++a) {
      const float invD = 1.f / r.direction[a];
      float t0 = (min_[a] - r.origin[a]) * invD;
      float t1 = (max_[a] - r.origin[a]) * invD;
      if (invD < 0) {
        std::swap(t0, t1);
      }
      t_min = t0 > t_min ? t0 : t_min;
      t_max = t1 < t_max ? t1 : t_max;
      if (t_max <= t_min) return false;
    }
    return true;
  }

private:
  Point3f min_ = {};
  Point3f max_ = {};
};

constexpr bool operator==(const AABB& lhs, const AABB& rhs)
{
  return lhs.min() == rhs.min() && lhs.max() == rhs.max();
}

constexpr bool operator!=(const AABB& lhs, const AABB& rhs)
{
  return !(lhs == rhs);
}

/**
 * @brief Computes the bounding box for two AABBs
 */
constexpr AABB surrounding_box(const AABB box0, const AABB box1)
{
  return AABB{{std::min(box0.min().x, box1.min().x),
               std::min(box0.min().y, box1.min().y),
               std::min(box0.min().z, box1.min().z)},
              {std::max(box0.max().x, box1.max().x),
               std::max(box0.max().y, box1.max().y),
               std::max(box0.max().z, box1.max().z)}};
}

#endif // AABB_HPP
