#include "scene.hpp"

/**
 * @param r The ray to check intersection
 * @param t_min The minimum distance from ray origin to detect intersection
 * @param t_max The maximum distance from ray origin to detect intersection
 * @return std::nullopt if the ray do not intersect with the sphere,
 * a Hit_record struct if the ray intersects the sphere
 */
std::optional<Hit_record> Scene::intersect_at(const Ray &r, float t_min, float t_max) const noexcept
{
    std::optional<Hit_record> temp_record = std::nullopt;
    auto closest_so_far = t_max;

    for (const auto& sphere : spheres_) {
        auto hit = sphere.intersect_at(r, t_min, closest_so_far);
        if (hit) {
            closest_so_far = hit->t;
            temp_record = *hit;
        }
    }

    return temp_record;
}


