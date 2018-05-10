#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include <type_traits>

#include "camera.hpp"
#include "sphere.hpp"

/**
 * @brief The Scene class represent the scene to be rendered by Path tracer
 */
class Scene
{
public:
    explicit Scene(Camera camera) noexcept :camera_{camera} {}

    /**
     *  @brief Adds an Hitable object to the scene
     */
    template <typename T, class ...Args>
    void add_object(Args... args) noexcept;

    /**
     * @brief Returns the hit record at the closet hit point
     */
    std::optional<Hit_record> intersect_at(const Ray& r,
                                           float t_min,
                                           float t_max) const noexcept;

    Camera camera() const noexcept
    {
        return camera_;
    }

private:
    Camera camera_;
    std::vector<Sphere> spheres_;
};

/**
 * @tparam T The type of Sphere object we want to add to the scene
 * @tparam ...Args Type of the arguments passed to your object constructor
 * @param args The arguments passed to your object constructor
 */
template <class T, class ... Args>
void Scene::add_object(Args... args) noexcept {
    if constexpr (std::is_same<T, Sphere>::value) {
        spheres_.emplace_back(std::forward<Args>(args)...);
    } else {
        static_assert(!std::is_same<T,T>::value, "Unsupported object primitive type");
    }
}

#endif // SCENE_HPP
