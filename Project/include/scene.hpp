#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <type_traits>
#include <vector>

#include "camera.hpp"
#include "hitable.hpp"

/**
 * @brief The Scene class represent the scene to be rendered by Path tracer
 */
class Scene {
public:
  /**
   * @brief Constructs a Scene object
   * @param aggregate The combination of all objects in the scene
   */
  explicit Scene(std::unique_ptr<Hitable>&& aggregate) noexcept
      : aggregate_{std::move(aggregate)}
  {
  }

  /**
   * @brief Returns the hit record at the closet hit point
   */
  Maybe_hit_t intersect_at(const Ray& r) const noexcept;

private:
  std::unique_ptr<const Hitable> aggregate_ = nullptr;
};

#endif // SCENE_HPP
