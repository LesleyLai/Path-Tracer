#include <optional>
#include <random>

#include "material.hpp"
#include "vector.hpp"

namespace {
std::optional<Ray> lambertian_scatter(const Hit_record& record);

std::optional<Ray> metal_scatter(const Ray& ray_in, const Hit_record& record,
                                 float fuzzness);

std::optional<Ray> dielectric_scatter(const Ray& ray_in,
                                      const Hit_record& record,
                                      float refractive_index);
} // namespace

std::optional<Ray> Material::scatter(const Ray& ray_in,
                                     const Hit_record& record) const
{
  switch (type_) {
  case Type::Lambertian:
    return lambertian_scatter(record);
  case Type::Metal:
    return metal_scatter(ray_in, record, fuzzness_);
  case Type::Dielectric:
    return dielectric_scatter(ray_in, record, refractive_index_);
  }
  return {};
}

namespace {
constexpr Vec3f reflect(Vec3f v, Vec3f n) noexcept
{
  return v - 2 * dot(v, n) * n;
}

// Refraction by snell's law
std::optional<Vec3f> refract(Vec3f v, Vec3f n, float ni_over_nt) noexcept
{
  const auto uv = v / v.length();
  float dt = dot(uv, n);
  float discriminant = 1 - ni_over_nt * ni_over_nt * (1 - dt * dt);
  if (discriminant > 0) {
    return ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
  }
  return std::nullopt;
}

Vec3f random_in_unit_sphere()
{
  // Credit:
  // https://math.stackexchange.com/questions/87230/picking-random-points-in-the-volume-of-sphere-with-uniform-probability/87238#87238
  thread_local std::mt19937 gen = std::mt19937{std::random_device{}()};
  thread_local std::uniform_real_distribution<float> uni(-1, 1);
  thread_local std::normal_distribution<float> normal(0, 1);

  Vec3f p{normal(gen), normal(gen), normal(gen)};
  p.normalize();

  const auto c = std::cbrt(uni(gen));
  return p * c;
}

// Reflectivity by Christophe Schlick
float schlick(float cosine, float ref_idx)
{
  float r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 *= r0;
  return r0 + (1 - r0) * std::pow(1 - cosine, 5);
}

std::optional<Ray> lambertian_scatter(const Hit_record& record)
{
  Vec3f target = record.point + record.normal + random_in_unit_sphere();
  return Ray{record.point, target - record.point};
}

std::optional<Ray> metal_scatter(const Ray& ray_in, const Hit_record& record,
                                 float fuzzness)
{
  auto incident_dir = ray_in.direction / ray_in.direction.length();
  auto reflected =
      reflect(incident_dir, record.normal) + fuzzness * random_in_unit_sphere();
  if (dot(reflected, record.normal) <= 0) {
    return std::nullopt;
  }

  Ray scattered{record.point, reflected};
  return scattered;
}

std::optional<Ray> dielectric_scatter(const Ray& ray_in,
                                      const Hit_record& record,
                                      float refractive_index)
{
  Vec3f out_normal;
  float ni_over_nt;
  float cosine;
  if (dot(ray_in.direction, record.normal) > 0) {
    out_normal = -record.normal;
    ni_over_nt = refractive_index;
    cosine = refractive_index * dot(ray_in.direction, record.normal) /
             ray_in.direction.length();
  }
  else {
    out_normal = record.normal;
    ni_over_nt = 1 / refractive_index;
    cosine = -dot(ray_in.direction, record.normal) / ray_in.direction.length();
  }

  float reflection_prob = 1;

  auto refraction = refract(ray_in.direction, out_normal, ni_over_nt);
  if (refraction) {
    reflection_prob = schlick(cosine, refractive_index);
  }

  static std::uniform_real_distribution<float> dis(0, 1);
  thread_local std::mt19937 gen = std::mt19937{std::random_device{}()};

  if (dis(gen) < reflection_prob) {
    auto incident_dir = ray_in.direction / ray_in.direction.length();
    auto reflection = reflect(incident_dir, record.normal);
    return Ray(record.point, reflection);
  }
  return Ray(record.point, *refraction);
}
} // namespace
