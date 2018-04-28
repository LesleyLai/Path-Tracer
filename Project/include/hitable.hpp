#ifndef HITABLE_HPP
#define HITABLE_HPP

#include <optional>
#include "vector.hpp"

struct Ray;
class Material;

/**
 * @brief Data recorded for a ray-object intersection
 */
struct Hit_record {
    double t;
    Vec3d point; ///< Intersection point
    Vec3d normal; ///< Surface normal, need to be construct as a unit vector
    const Material* material;
};

/**
 * @brief The Hitable interface represented an physical object that can be hited
 * by ray
 */
class Hitable {
public:
    /**
     * @brief Create a hitable object with certain material
     */
    Hitable(const Material* mat) : mat_{mat} {}

    virtual ~Hitable() = default;
    Hitable(const Hitable&) noexcept = default;
    Hitable& operator=(const Hitable&) noexcept = default;
    Hitable(Hitable&&) noexcept = default;
    Hitable& operator=(Hitable&&) noexcept = default;

    /**
     * @brief Ray-object intersection detection
     * @param r The ray to check intersection
     * @return std::nullopt if the ray do not intersect with the sphere,
     * a Hit_record struct if the ray intersects the sphere
     */
    virtual std::optional<Hit_record> intersect_at(const Ray& r, double t_min, double t_max) noexcept = 0;

    const Material& material() const {
        return *mat_;
    }

protected:
    Hitable() noexcept = default;

private:
    const Material* mat_ = nullptr;
};

#endif // HITABLE_HPP
