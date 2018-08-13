#ifndef AXIS_ALIGNED_RECT_HPP
#define AXIS_ALIGNED_RECT_HPP

#include "hitable.hpp"
#include "material.hpp"
#include "point.hpp"

struct Rect_XY : Hitable {
  Point2f min;
  Point2f max;
  float z;

  Rect_XY(Point2f in_min, Point2f in_max, float in_z, const Material& mat)
      : min{in_min}, max{in_max}, z{in_z}, material{&mat}
  {
  }

  std::optional<AABB> bounding_box() const noexcept override
  {
    return AABB{{min, z - 0.0001f}, {max, z + 0.0001f}};
  }

  Maybe_hit_t intersect_at(const Ray& r, float t_min, float t_max) const
      noexcept override;

  const Material* const material;
};

#endif // AXIS_ALIGNED_RECT_HPP
