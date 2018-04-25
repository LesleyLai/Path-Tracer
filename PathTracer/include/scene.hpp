#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>

#include "hitable.hpp"


class Scene
{
public:
    Scene() noexcept = default;

    template <typename T, class ...Args>
    void add_object(Args... args) noexcept;

    /**
     * @brief Returns the hit record at the closet hit point
     */
    std::optional<Hit_record> intersect_at(const Ray& r, double t_min, double t_max) const noexcept;

private:
    std::vector<std::unique_ptr<Hitable>> objects_;
};

template <typename T, class ... Args>
void Scene::add_object(Args... args) noexcept {
    objects_.push_back(std::make_unique<T>(args...));
}

#endif // SCENE_HPP
