#include "bounding_value_hierarchy.hpp"

#include <algorithm>
#include <cassert>
#include <random>

BVH_node::BVH_node(const Object_iterator& begin,
                   const Object_iterator& end) noexcept
{
  thread_local std::mt19937 gen = std::mt19937{std::random_device{}()};
  std::uniform_int_distribution<int> dis(0, 2);
  int axis = dis(gen);
  if (axis == 0) {
    // Sort by x
    std::sort(begin, end,
              [](const std::unique_ptr<Hitable>& lhs,
                 const std::unique_ptr<Hitable>& rhs) {
                return lhs->bounding_box()->min().x <
                       rhs->bounding_box()->min().x;
              });
  }
  else if (axis == 1) {
    // Sort by y
    std::sort(begin, end,
              [](const std::unique_ptr<Hitable>& lhs,
                 const std::unique_ptr<Hitable>& rhs) {
                return lhs->bounding_box()->min().y <
                       rhs->bounding_box()->min().y;
              });
  }
  else {
    // Sort by z
    std::sort(begin, end,
              [](const std::unique_ptr<Hitable>& lhs,
                 const std::unique_ptr<Hitable>& rhs) {
                return lhs->bounding_box()->min().z <
                       rhs->bounding_box()->min().z;
              });
  }

  const auto size = end - begin;
  assert(size > 0);
  if (size == 1) {
    left_ = right_ = begin->get();
  }
  else if (size == 2) {
    auto itr = begin;
    left_ = itr->get();
    ++itr;
    right_ = itr->get();
  }
  else {
    left_ = new BVH_node(begin, begin + size / 2);
    right_ = new BVH_node(begin + size / 2, end);
  }

  assert(left_->bounding_box() != std::nullopt &&
         right_->bounding_box() != std::nullopt);
  box_ = surrounding_box(*left_->bounding_box(), *right_->bounding_box());
}

Maybe_hit_t BVH_node::intersect_at(const Ray& r, float t_min, float t_max) const
    noexcept
{
  assert(left_ != nullptr && right_ != nullptr);

  if (!box_.hit(r, t_min, t_max)) {
    return {};
  }

  const auto hit_left_record = left_->intersect_at(r, t_min, t_max);
  const auto hit_right_record = right_->intersect_at(r, t_min, t_max);
  if (hit_left_record && hit_right_record) {
    if (hit_left_record->t < hit_right_record->t) {
      return hit_left_record;
    }
    else {
      return hit_right_record;
    }
  }
  else if (hit_left_record) {
    return hit_left_record;
  }
  else if (hit_right_record) {
    return hit_right_record;
  }
  else {
    return {};
  }
}
