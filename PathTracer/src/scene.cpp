#include <limits>
#include "scene.hpp"

std::optional<Hit_record> Scene::intersect_at(const Ray &r) const noexcept
{
    std::optional<Hit_record> temp_record = std::nullopt;
    auto closest_so_far = std::numeric_limits<double>::infinity();

    for (const auto& object : objects_) {
        auto hit = object->intersect_at(r);
        if (hit && hit->t < closest_so_far) {
            closest_so_far = hit->t;
            temp_record = *hit;
        }
    }

    return temp_record;
}
