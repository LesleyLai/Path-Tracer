#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>

#include "hitable.hpp"

/**
 * @brief The Scene class represent the scene to be rendered by Path tracer
 */
class Scene
{
public:
    Scene() noexcept {}

    /**
     *  @brief Adds an Hitable object to the scene
     */
    template <typename T, class ...Args>
    void add_object(Args... args) noexcept;

    /**
     * @brief Returns the hit record at the closet hit point
     */
    std::optional<Hit_record> intersect_at(const Ray& r, double t_min, double t_max) const noexcept;

private:
    std::vector<std::unique_ptr<Hitable>> objects_;
};

/**
 * @tparam T The type of Hitable object we want to add to the scene
 * @tparam ...Args Type of the arguments passed to your object constructor
 * @param args The arguments passed to your object constructor
 */
template <typename T, class ... Args>
void Scene::add_object(Args... args) noexcept {
    objects_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}

#endif // SCENE_HPP
