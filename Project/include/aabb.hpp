#ifndef AABB_HPP
#define AABB_HPP

#include "ray.hpp"
#include "vector.hpp"

/**
 * @brief 3d Axis aligned bounding boxes are used for bounding volume
 * hierarchies
 */
class AABB {
public:
  constexpr AABB() noexcept = default;

  /**
   * @brief Construction an AABB from its minimal corner to maximum corner
   */
  constexpr AABB(Vec3f min, Vec3f max) noexcept : min_{min}, max_{max} {}

  constexpr Vec3f min() const { return min_; }
  constexpr Vec3f max() const { return max_; }

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
  Vec3f min_ = {};
  Vec3f max_ = {};
};

#endif // AABB_HPP
