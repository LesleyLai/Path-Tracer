#include "axis_aligned_rect.hpp"

Vec3f flip_negative_normal(Vec3f normal, Normal_Direction d)
{
  return d == Normal_Direction::Negetive ? -normal : normal;
}

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

  return Hit_record{t, r.point_at_parameter(t),
                    flip_negative_normal(Vec3f(0, 0, 1), direction), material};
}

Maybe_hit_t Rect_XZ::intersect_at(const Ray& r, float t_min, float t_max) const
    noexcept
{
  const float t = (y - r.origin.y) / r.direction.y;
  if (t < t_min || t > t_max) {
    return {};
  }

  const float x = r.origin.x + t * r.direction.x;
  const float z = r.origin.z + t * r.direction.z;
  if (x < min.x || x > max.x || z < min.y || z > max.y) {
    return std::nullopt;
  }

  return Hit_record{t, r.point_at_parameter(t),
                    flip_negative_normal(Vec3f(0, 1, 0), direction), material};
}

Maybe_hit_t Rect_YZ::intersect_at(const Ray& r, float t_min, float t_max) const
    noexcept
{
  const float t = (x - r.origin.x) / r.direction.x;
  if (t < t_min || t > t_max) {
    return {};
  }

  const float y = r.origin.y + t * r.direction.y;
  const float z = r.origin.z + t * r.direction.z;
  if (y < min.x || y > max.x || z < min.y || z > max.y) {
    return std::nullopt;
  }

  return Hit_record{t, r.point_at_parameter(t),
                    flip_negative_normal(Vec3f(1, 0, 0), direction), material};
}
