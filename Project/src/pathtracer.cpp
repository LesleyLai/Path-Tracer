#include "pathtracer.hpp"

#include <iostream>
#include <limits>
#include <random>
#include <memory>
#include <future>

#include "camera.hpp"
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "image.hpp"
#include "scene.hpp"

Color trace(const Scene &scene, const Ray &ray, size_t depth=0) noexcept
{
    constexpr double inf = std::numeric_limits<double>::infinity();
    constexpr size_t max_depth = 100;

    // depth exceed some threshold
    if (depth >= max_depth) {
        return Color{}; // return black
    }

    if (auto hit = scene.intersect_at(ray, 0.0001f, inf)) {
        auto material = hit->material;
        auto ref = material->scatter(ray, *hit);
        if (ref) {
            return material->albedo() * trace(scene, *ref, depth+1);
        }
            return Color{};
    }

    const auto unit_direction = ray.direction / ray.direction.length();
    const auto t = 0.5f * (unit_direction.y + 1);
    return (1.f - t) * Color{1,1,1} + t * Color(0.5f, 0.7f, 1);
}

struct PixelData {
    Color c;
    size_t x;
    size_t y;
};


void Path_tracer::run(const Scene& scene, Image& image, size_t sample_per_pixel)
{
    const auto width = image.width(), height = image.height();


    std::vector<std::future<PixelData>> results;
    for (size_t j = 0; j < height; ++j) {
        for (size_t i = 0; i < width; ++i) {
            results.push_back(std::async(std::launch::async, [i, j, sample_per_pixel, width, height, &scene]{
                    Color c;

                    thread_local std::mt19937 gen = std::mt19937{ std::random_device{}() }; //Standard mersenne_twister_engine seeded with rd()
                    std::uniform_real_distribution<float> dis(0.0, 1.0);

                    for (size_t sample = 0; sample < sample_per_pixel; ++sample) {
                        const float u = (i + dis(gen)) / width;
                        const float v = (j + dis(gen)) / height;

                        const auto r = scene.camera().getRay(u, v);
                        c += trace(scene, r);
                    }
                    c /= static_cast<float>(sample_per_pixel);
                    return PixelData {c, i, j};
            }));
        }

        for (auto& result : results) {
            result.wait();
            auto [color, i, j] = result.get();
            image.color_at(i, j) = color;
        }
        results.clear();
        std::cout << (j / static_cast<double>(height) * 100) << "%\n" << std::flush;
        }
}


