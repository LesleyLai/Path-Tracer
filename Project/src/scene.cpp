#include "scene.hpp"

std::optional<Hit_record> Scene::intersect_at(const Ray &r, double t_min, double t_max) const noexcept
{
    std::optional<Hit_record> temp_record = std::nullopt;
    auto closest_so_far = t_max;

    for (const auto& object : objects_) {
        auto hit = object->intersect_at(r, t_min, closest_so_far);
        if (hit) {
            closest_so_far = hit->t;
            temp_record = *hit;
        }
    }

    return temp_record;
}
