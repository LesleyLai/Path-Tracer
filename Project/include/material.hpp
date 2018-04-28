#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <optional>

#include "color.hpp"
#include "hitable.hpp"
#include "ray.hpp"

class Material {
public:
    enum class Type {
        Lambertian,
        Metal
    };

    Material(Color albedo) noexcept : albedo_{albedo} {}

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

class Lambertian : public Material {
public:
    Lambertian(Color albedo) noexcept : Material{albedo} {}

    std::optional<Ray>
    scatter(const Ray& ray_in, const Hit_record& record) const override;
};

class Metal : public Material {
public:
    Metal(Color albedo) noexcept : Material{albedo} {}

    std::optional<Ray>
    scatter(const Ray& ray_in, const Hit_record& record) const override;
};

#endif // MATERIAL_HPP
