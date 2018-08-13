#include "axis_aligned_rect.hpp"

Maybe_hit_t Rect_XY::intersect_at(const Ray& r, float t_min, float t_max) const
    noexcept
{
  const float t = (z - r.origin.z) / r.direction.z;
  if (t < t_min || t > t_max) {
    return {};
  }

  const float x = r.origin.x + t * r.direction.x;
  const float y = r.origin.y + t * r.direction.y;
  if (x < min.x || x > max.x || y < min.y || y > max.y) {
    return std::nullopt;
  }

  return Hit_record{t, r.point_at_parameter(t), Vec3f(0, 0, 1), material};
}
