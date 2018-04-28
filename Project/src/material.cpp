#include <optional>
#include <random>

#include "vector.hpp"
#include "material.hpp"

// Standard mersenne_twister_engine
static std::mt19937 gen = std::mt19937{ std::random_device{}() }; //Standard mersenne_twister_engine seeded with rd()

constexpr Vec3d reflect(Vec3d v, Vec3d n) noexcept {
    return v - 2 * dot(v, n) * n;
}

// Refraction by snell's law
constexpr std::optional<Vec3d> refract(Vec3d v, Vec3d n, double ni_over_nt) noexcept {
    const auto uv = v / v.length();
    double dt = dot(uv, n);
    double discriminant = 1 - ni_over_nt*ni_over_nt*(1-dt*dt);
    if (discriminant > 0) {
        return ni_over_nt * (uv - n*dt) - n * std::sqrt(discriminant);
    }
        return std::nullopt;
}

Vec3d random_in_unit_circle() {
    static const std::uniform_real_distribution<> dis(-1, 1);
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

// Reflectivity by Christophe Schlick
double schlick(double cosine, double ref_idx) {
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 *= r0;
    return r0 + (1-r0) * std::pow(1-cosine, 5);
}

std::optional<Ray> Dielectric::scatter(const Ray &ray_in, const Hit_record &record) const
{
    Vec3d out_normal;
    double ni_over_nt;
    double cosine;
    if (dot(ray_in.direction, record.normal) > 0) {
        out_normal = -record.normal;
        ni_over_nt = refractive_index_;
        cosine = refractive_index_ * dot(ray_in.direction, record.normal) / ray_in.direction.length();
    } else {
        out_normal = record.normal;
        ni_over_nt = 1 / refractive_index_;
        cosine = -dot(ray_in.direction, record.normal) / ray_in.direction.length();
    }

    double reflection_prob = 1;

    auto refraction = refract(ray_in.direction, out_normal, ni_over_nt);
    if (refraction) {
        reflection_prob = schlick(cosine, refractive_index_);
    }

    static const std::uniform_real_distribution<> dis(0, 1);
    if (dis(gen) < reflection_prob) {
        auto incident_dir = ray_in.direction / ray_in.direction.length();
        auto reflection = reflect(incident_dir, record.normal);
        return Ray(record.point, reflection);
    }
        return Ray(record.point, *refraction);
}
