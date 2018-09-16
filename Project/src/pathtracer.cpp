#include "pathtracer.hpp"

#include <future>
#include <iostream>
#include <memory>
#include <random>

#include "camera.hpp"
#include "color.hpp"
#include "image.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "scene.hpp"

Color trace(const Scene& scene, const Ray& ray, size_t depth = 0) noexcept
{
  constexpr size_t max_depth = 100;

  // depth exceed some threshold
  if (depth >= max_depth) {
    return Color{}; // return black
  }

  if (auto hit = scene.intersect_at(ray)) {
    auto material = hit->material;
    auto ref = material->scatter(ray, *hit);
    const auto emitted = material->emitted();
    if (ref) {
      return emitted + material->albedo() * trace(scene, *ref, depth + 1);
    }
    return emitted;
  }

  // Returns black if ray does not hit any object
  return Color{};
}

struct PixelData {
  size_t x{};
  size_t y{};
  Color c;
};

void Path_tracer::run(const Scene& scene, const Camera& camera, Image& image,
                      size_t sample_per_pixel)
{
  const auto width = image.width(), height = image.height();

  std::vector<std::future<PixelData>> results;
  for (size_t j = 0; j < height; ++j) {
    for (size_t i = 0; i < width; ++i) {
      results.push_back(std::async(std::launch::async, [i, j, sample_per_pixel,
                                                        width, height, &scene,
                                                        &camera] {
        Color c;
        thread_local std::mt19937 gen = std::mt19937{std::random_device{}()};
        std::uniform_real_distribution<float> dis(0.0, 1.0);

        for (size_t sample = 0; sample < sample_per_pixel; ++sample) {
          const float u = (i + dis(gen)) / width;
          const float v = (j + dis(gen)) / height;

          const auto r = camera.get_ray(u, v);
          c += trace(scene, r);
        }
        c /= static_cast<float>(sample_per_pixel);
        return PixelData{i, j, c};
      }));
    }

    for (auto& result : results) {
      result.wait();
      auto [i, j, color] = result.get();
      image.color_at(i, j) = color;
    }
    results.clear();
    std::cout << (j / static_cast<double>(height) * 100) << "%\n" << std::flush;
  }
}
