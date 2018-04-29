#include "pathtracer.hpp"

#include <iostream>
#include <limits>
#include <random>
#include <memory>

#include "camera.hpp"
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "image.hpp"
#include "scene.hpp"

Color Path_tracer::trace(const Scene &scene, const Ray &ray, size_t depth) const noexcept
{
    constexpr double inf = std::numeric_limits<double>::infinity();
    constexpr size_t max_depth = 50;

    // depth exceed some threshold
    if (depth >= max_depth) {
        return Color{}; // return black
    }

    if (auto hit = scene.intersect_at(ray, 0.0001, inf)) {
        auto material = hit->material;
        auto ref = material->scatter(ray, *hit);
        if (ref) {
            return material->albedo() * trace(scene, *ref, depth+1);
        }
            return Color{};
    }

    const auto unit_direction = ray.direction / ray.direction.length();
    const auto t = static_cast<float>(0.5 * (unit_direction.y + 1));
    return (1.f - t) * Color{1,1,1} + t * Color(0.5f, 0.7f, 1);
}

void Path_tracer::run(const Scene& scene, Image& image, size_t sample_per_pixel)
{
    const auto width = image.width(), height = image.height();

    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (size_t j = 0; j < height; ++j) {
        for (size_t i = 0; i < width; ++i) {
            Color c;
            for (index_t sample = 0; sample < sample_per_pixel; ++sample) {
                const double u = (i + dis(gen)) / width;
                const double v = (j + dis(gen)) / height;

                const auto r = scene.camera().getRay(u, v);
                c += trace(scene, r);
            }
            c /= static_cast<float>(sample_per_pixel);
            image.color_at(i, j) = c;
        }
        std::cout << (j / static_cast<double>(height) * 100) << "%\n" << std::flush;
    }
}


