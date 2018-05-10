#include "sphere.hpp"
#include "ray.hpp"

std::optional<Hit_record> Sphere::intersect_at(const Ray &r, float t_min, float t_max) const noexcept {
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

    auto hit_record_from_t = [&r, this](float t) {
        const auto point = r.point_at_parameter(t);
        const auto normal = (point - center) / radius;

        Hit_record record{t, point, normal, &material};
        return std::optional<Hit_record>{std::in_place, record};
	};

    // Get the smaller non-negative value of t1, t2
    if (t1 >= t_min && t1 < t_max) {
        return hit_record_from_t(t1);
    }
    if (t2 >= t_min && t2 < t_max) {
        return hit_record_from_t(t2);
    }
    return std::nullopt;
}
