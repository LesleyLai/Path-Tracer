#include <chrono>
#include <cstdio>
#include <memory>
#include <random>
#include <stdexcept>
#include <vector>

#include <fmt/printf.h>

#include "axis_aligned_rect.hpp"
#include "bounding_volume_hierarchy.hpp"
#include "image.hpp"
#include "material.hpp"
#include "pathtracer.hpp"
#include "scene.hpp"
#include "sphere.hpp"

namespace {
const Lambertian red{Color(0.65f, 0.05f, 0.05f)};
const Lambertian white{Color(0.73f, 0.73f, 0.73f)};
const Lambertian green{Color(0.12f, 0.45f, 0.15f)};
const Emission light{Color(15, 15, 15)};
} // namespace

Scene create_scene()
{
  std::vector<std::unique_ptr<Hitable>> objects;
  std::vector<std::unique_ptr<Material>> materials;

  objects.push_back(std::make_unique<Rect_YZ>(Point2f(0, 0), Point2f(555, 555),
                                              555, green,
                                              Normal_Direction::Negetive));
  objects.push_back(
      std::make_unique<Rect_YZ>(Point2f(0, 0), Point2f(555, 555), 0, red));

  objects.push_back(std::make_unique<Rect_XZ>(Point2f(213, 227),
                                              Point2f(343, 332), 554, light));
  objects.push_back(std::make_unique<Rect_XZ>(Point2f(0, 0), Point2f(555, 555),
                                              555, white,
                                              Normal_Direction::Negetive));
  objects.push_back(
      std::make_unique<Rect_XZ>(Point2f(0, 0), Point2f(555, 555), 0, white));

  objects.push_back(std::make_unique<Rect_XY>(Point2f(0, 0), Point2f(555, 555),
                                              555, white,
                                              Normal_Direction::Negetive));

  return Scene(std::make_unique<BVH_node>(objects.begin(), objects.end()),
               std::move(materials));
}

template <typename Duration>
void print_elapse_time(const Duration& elapsed_time)
{
  using namespace std::chrono;

  if (elapsed_time < 1s) {
    fmt::print("{}ms\n", duration_cast<milliseconds>(elapsed_time).count());
  }
  else if (elapsed_time < 1min) {
    fmt::print("{}s\n", duration_cast<seconds>(elapsed_time).count());
  }
  else {
    auto s = duration_cast<seconds>(elapsed_time).count();
    fmt::print("{}min {}s\n", s / 60, s % 60);
  }
}

int main() try {
  using namespace std::chrono;

  Path_tracer path_tracer;

  constexpr int width = 800, height = 600;
  Image image(width, height);

  constexpr auto aspect_ratio = static_cast<float>(width) / height;
  Camera camera{
      {278, 278, -800}, {278, 278, 0}, {0, 1, 0}, 40.0_deg, aspect_ratio};
  const auto scene = create_scene();

  auto start = std::chrono::system_clock::now();
  path_tracer.run(scene, camera, image, 5);
  auto end = std::chrono::system_clock::now();

  std::puts("elapsed time: ");
  print_elapse_time(end - start);

  std::string filename{"test.png"};
  image.saveto(filename);
  fmt::print("Save image to {}.\n", filename);
  return 0;
}
catch (const Cannot_write_file& e) {
  fmt::print("Cannot write to file: {}\n", e.what());
  return -1;
}
catch (const Unsupported_image_extension& e) {
  fmt::print(stderr, "Unsupported image extension: {}\n", e.what());
  fmt::print(stderr, "Currently: only ppm output is supported\n");
  return -2;
}
catch (const std::exception& e) {
  fmt::print(stderr, "Error: {}", e.what());
  throw e;
}
catch (...) {
  std::fputs("Unknown exception\n", stderr);
  return -255;
}
