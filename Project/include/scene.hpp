#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <type_traits>
#include <vector>

#include "bounding_value_hierarchy.hpp"
#include "camera.hpp"
#include "hitable.hpp"

/**
 * @brief The Scene class represent the scene to be rendered by Path tracer
 */
class Scene {
public:
  Scene() noexcept = default;

  /**
   *  @brief Adds an Hitable object to the scene
   */
  template <typename T, class... Args> void add_object(Args... args) noexcept;

  // Create bounding value hierarchy by the current objects in the scene
  void create_bvh()
  {
    bvh_ = std::make_unique<BVH_node>(std::begin(objects_), std::end(objects_));
  }

  /**
   * @brief Returns the hit record at the closet hit point
   */
  Maybe_hit_t intersect_at(const Ray& r, float t_min, float t_max) const
      noexcept;

private:
  std::vector<std::unique_ptr<Hitable>> objects_;
  std::unique_ptr<BVH_node> bvh_ = nullptr;
};

/**
 * @tparam T The type of Sphere object we want to add to the scene
 * @tparam ...Args Type of the arguments passed to your object constructor
 * @param args The arguments passed to your object constructor
 */
template <class T, class... Args> void Scene::add_object(Args... args) noexcept
{
  if constexpr (std::is_base_of<Hitable, T>::value) {
    objects_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
  }
  else {
    static_assert(!std::is_same<T, T>::value,
                  "Unsupported object primitive type");
  }
}

#endif // SCENE_HPP
