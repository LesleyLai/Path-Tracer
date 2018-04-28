#include "vector.hpp"
#include "material.hpp"

constexpr Vec3d reflect(Vec3d v, Vec3d n) noexcept {
    return v - 2 * dot(v, n) * n;
}

template <typename Random_generator>
Vec3d random_in_unit_circle(Random_generator& gen) noexcept {
    // Standard mersenne_twister_engine seeded with rd()
    Vec3d p;
    do {
        p = Vec3d(dis(gen), dis(gen), dis(gen));
    } while (p.length_square() >= 1);
    return p;
}

std::optional<Ray>
Material::scatter(const Ray &ray_in, const Hit_record &record) const noexcept
{
    switch (type_) {
    case Type::Lambertian:
        Vec3d target = hit->point + hit->normal + random_in_unit_circle(gen);
         return damping * trace(scene, Ray{hit->point, target - hit->point}, depth-1);
        break;
    case Type::Reflect:
        auto incident_dir = ray_in.direction / ray_in.direction.length();
        auto reflected = reflect(incident_dir, record.normal);
        if (dot(reflected, record.normal) <= 0) {
            return std::nullopt;
        }

        Ray scattered {record.point, reflected};
        return scattered;
    }


}
