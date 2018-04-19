#include "sphere.hpp"
#include "ray.hpp"

std::optional<Hit_record> Sphere::intersect_at(const Ray &r) noexcept {
    const auto oc = r.origin - center;

    const auto a = dot(r.direction, r.direction);
    const auto b = 2 * dot(r.direction, oc);
    const auto c = dot(oc, oc) - radius * radius;
    const auto discrimination = b * b - 4 * a * c;

    if (discrimination < 0) {
        return std::nullopt;
    }

    auto hit_record_from_t = [&r, this](double t) {
        Hit_record record{};
        record.t = t;
        record.point = r.point_at_parameter(record.t);
        record.normal = (record.point - center) / radius;
        return record;
    };

    const auto sqrt_delta = std::sqrt(discrimination);
    const auto t1 = (-b - sqrt_delta) / (2*a);
    const auto t2 = (-b + sqrt_delta) / (2*a);

    // Get the smaller non-negative value of t1, t2
    if (t1 >= 0) {
        return hit_record_from_t(t1);
    }
    if (t2 >= 0) {
        return hit_record_from_t(t2);
    }
    return std::nullopt;
}
