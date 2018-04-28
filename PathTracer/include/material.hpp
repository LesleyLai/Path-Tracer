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
        Reflect
    };

    constexpr Material() noexcept = default;
    constexpr Material(float albedo, Type type) noexcept : albedo_{albedo}, type_{type} {}

    /**
     * @brief scatter
     * @param ray_in Incident ray
     * @param record
     * @return scattered ray if the incident ray is not absorbed
     */
    std::optional<Ray>
    scatter(const Ray& ray_in, const Hit_record& record) const noexcept;
private:
    Type type_ = Type::Lambertian;
    float albedo_ = 0.5f;
};

#endif // MATERIAL_HPP
