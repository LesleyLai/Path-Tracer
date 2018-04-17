#include "sphere.hpp"

std::optional<double> Sphere::intersect_at(const Ray &r) noexcept {
    const auto oc = r.origin - center;

    const auto a = dot(r.direction, r.direction);
    const auto b = 2 * dot(r.direction, oc);
    const auto c = dot(oc, oc) - radius * radius;
    const auto discrimination = b * b - 4 * a * c;

    if (discrimination < 0) {
        return std::nullopt;
    }

    const auto sqrt_delta = std::sqrt(discrimination);
    const auto t1 = (-b - sqrt_delta) / (2*a);
    const auto t2 = (-b + sqrt_delta) / (2*a);

    // Get the smaller non-negative value of t1, t2
    if (t1 >= 0) {
        return t1;
    }
    if (t2 >= 0) {
        return t2;
    }
    return std::nullopt;
}
