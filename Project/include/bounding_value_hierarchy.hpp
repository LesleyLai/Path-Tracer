#ifndef BOUNDING_VALUE_HIERARCHY_HPP
#define BOUNDING_VALUE_HIERARCHY_HPP

#include <memory>
#include <vector>

#include "aabb.hpp"
#include "hitable.hpp"

using Object_iterator = std::vector<std::unique_ptr<Hitable>>::iterator;

class BVH_node : public Hitable {
public:
  BVH_node(const Object_iterator& begin, const Object_iterator& end) noexcept;

  std::optional<AABB> bounding_box() const noexcept override { return box_; }

  Maybe_hit_t intersect_at(const Ray& r, float t_min, float t_max) const
      noexcept override;

private:
  Hitable* left_ = nullptr;
  Hitable* right_ = nullptr;
  AABB box_;
};

#endif // BOUNDING_VALUE_HIERARCHY_HPP
