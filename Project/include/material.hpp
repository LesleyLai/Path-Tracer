#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <optional>
#include <variant>

#include "angle.hpp"
#include "color.hpp"
#include "hitable.hpp"
#include "ray.hpp"

class Material {
public:
  Material() noexcept = default;
  explicit Material(Color albedo) noexcept : albedo_{albedo} {}
  virtual ~Material() = default;

  /**
   * @brief scatter
   * @param ray_in Incident ray
   * @param record
   * @return scattered ray if the incident ray is not absorbed
   */
  virtual std::optional<Ray> scatter(const Ray& ray_in,
                                     const Hit_record& record) const = 0;

  virtual Color emitted() const { return Color{}; }

  constexpr Color albedo() const noexcept { return albedo_; }

private:
  Color albedo_{0.5f, 0.5f, 0.5f};
};

class Lambertian : public Material {
public:
  explicit Lambertian(Color albedo) noexcept : Material{albedo} {}

  std::optional<Ray> scatter(const Ray& ray_in,
                             const Hit_record& record) const override;
};

class Metal : public Material {
public:
  Metal(Color albedo, float fuzzness) noexcept
      : Material{albedo}, fuzzness_{fuzzness}
  {
  }

  std::optional<Ray> scatter(const Ray& ray_in,
                             const Hit_record& record) const override;

private:
  float fuzzness_;
};

class Dielectric : public Material {
public:
  Dielectric(Color albedo, float fuzzness, float refractive_index) noexcept
      : Material{albedo}, fuzzness_{fuzzness}, refractive_index_{
                                                   refractive_index}
  {
  }

  std::optional<Ray> scatter(const Ray& ray_in,
                             const Hit_record& record) const override;

private:
  float fuzzness_;
  float refractive_index_;
};

class Emission : public Material {
public:
  explicit Emission(Color emit) noexcept : emit_(emit) {}

  std::optional<Ray> scatter(const Ray& ray_in,
                             const Hit_record& record) const override;
  Color emitted() const override;

private:
  Color emit_;
};

#endif // MATERIAL_HPP
