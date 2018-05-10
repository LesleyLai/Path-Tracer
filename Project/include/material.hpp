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
        Metal,
        Dielectric
    };

    Material(Type type,
             Color albedo,
             float fuzzness = 0,
             float refractive_index = 0) noexcept :
        type_{type},
        albedo_{albedo},
        fuzzness_{fuzzness},
        refractive_index_{refractive_index}
    {}

    /**
     * @brief scatter
     * @param ray_in Incident ray
     * @param record
     * @return scattered ray if the incident ray is not absorbed
     */
    std::optional<Ray>
    scatter(const Ray& ray_in, const Hit_record& record) const;

    constexpr Color albedo() const noexcept
    {
        return albedo_;
    }

private:
    Type type_;
    Color albedo_ {0.5f, 0.5f, 0.5f};
    float fuzzness_;
    float refractive_index_;
};

#endif // MATERIAL_HPP
