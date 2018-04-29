#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <optional>

#include "angle.hpp"
#include "color.hpp"
#include "hitable.hpp"
#include "ray.hpp"

class Material {
public:
    enum class Type {
        Lambertian,
        Metal
    };

    explicit Material(Color albedo) noexcept : albedo_{albedo} {}

    virtual ~Material() = default;
    Material(const Material&) noexcept = default;
    Material& operator=(const Material&) noexcept = default;
    Material(Material&&) noexcept = default;
    Material& operator=(Material&&) noexcept = default;

    /**
     * @brief scatter
     * @param ray_in Incident ray
     * @param record
     * @return scattered ray if the incident ray is not absorbed
     */
    std::optional<Ray>
    virtual scatter(const Ray& ray_in, const Hit_record& record) const = 0;

    constexpr Color albedo() const noexcept
    {
        return albedo_;
    }

private:
    Color albedo_ {0.5f, 0.5f, 0.5f};
};

/**
 * @brief Lambertian materials only have diffuse reflection
 */
class Lambertian : public Material {
public:
    explicit Lambertian(Color albedo) noexcept : Material{albedo} {}

    std::optional<Ray>
    scatter(const Ray& ray_in, const Hit_record& record) const override;
};


class Metal : public Material {
public:
    Metal(Color albedo, float fuzzness) noexcept : Material{albedo}, fuzzness_{fuzzness} {}

    std::optional<Ray>
    scatter(const Ray& ray_in, const Hit_record& record) const override;

private:
    float fuzzness_;
};

class Dielectric : public Material {
public:
    Dielectric(Color albedo, float refractive_index) noexcept : Material{albedo},
        refractive_index_{refractive_index} {}

    std::optional<Ray>
    scatter(const Ray& ray_in, const Hit_record& record) const override;

private:
    float refractive_index_;
};

#endif // MATERIAL_HPP
