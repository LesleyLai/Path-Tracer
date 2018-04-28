#include <random>

#include "vector.hpp"
#include "material.hpp"

constexpr Vec3d reflect(Vec3d v, Vec3d n) noexcept {
    return v - 2 * dot(v, n) * n;
}

Vec3d random_in_unit_circle() {
    static std::mt19937 gen = std::mt19937{ std::random_device{}() }; //Standard mersenne_twister_engine seeded with rd()
    static const std::uniform_real_distribution<> dis(-1, 1);

    // Standard mersenne_twister_engine seeded with rd()
    Vec3d p;
    do {
        p = Vec3d(dis(gen), dis(gen), dis(gen));
    } while (p.length_square() >= 1);
    return p;
}

std::optional<Ray> Lambertian::scatter(const Ray& /*ray_in*/, const Hit_record& record) const
{
    Vec3d target = record.point + record.normal + random_in_unit_circle();
    return Ray{record.point, target - record.point};
}

std::optional<Ray> Metal::scatter(const Ray& ray_in, const Hit_record& record) const
{
    auto incident_dir = ray_in.direction / ray_in.direction.length();
    auto reflected = reflect(incident_dir, record.normal) + fuzzness_ * random_in_unit_circle();
    if (dot(reflected, record.normal) <= 0) {
        return std::nullopt;
    }

    Ray scattered {record.point, reflected};
    return scattered;
}
