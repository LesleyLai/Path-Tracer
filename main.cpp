#include <chrono>
#include <cstdio>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <vector>

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
const Emission light{Color(1, 1, 1)};
const Metal metal{Color(0.73f, 0.73f, 0.73f), 0.8};
const Dielectric glass(Color(1.f, 1.f, 1.f), 0.1, 1.655);
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

  objects.push_back(
      std::make_unique<Sphere>(Point3f{200, 100, 300}, 100, metal));

  objects.push_back(
      std::make_unique<Sphere>(Point3f{300, 110, 100}, 100, glass));

  return Scene(std::make_unique<BVH_node>(objects.begin(), objects.end()),
               std::move(materials));
}

template <typename Duration>
void print_elapse_time(const Duration& elapsed_time)
{
  using namespace std::chrono;

  if (elapsed_time < 1s) {
    std::cout << duration_cast<milliseconds>(elapsed_time).count() << "ms\n";
  }
  else if (elapsed_time < 1min) {
    std::cout << duration_cast<seconds>(elapsed_time).count() << "s\n";
  }
  else {
    auto s = duration_cast<seconds>(elapsed_time).count();
    std::cout << (s / 60) << "min " << (s % 60) << "s\n";
  }
}

int main()
try {
  using namespace std::chrono;

  Path_tracer path_tracer;

  constexpr int width = 800, height = 600;
  Image image(width, height);

  constexpr auto aspect_ratio = static_cast<float>(width) / height;
  Camera camera{
      {278, 278, -800}, {278, 278, 0}, {0, 1, 0}, 40.0_deg, aspect_ratio};
  const auto scene = create_scene();

  const auto start = std::chrono::system_clock::now();
  path_tracer.run(scene, camera, image, 500);
  const auto end = std::chrono::system_clock::now();

  std::puts("elapsed time: ");
  print_elapse_time(end - start);

  std::string filename{"test.png"};
  image.saveto(filename);
  std::cout << "Save image to " << filename << ".\n";
  return 0;
}
catch (const Cannot_write_file& e) {
  std::cerr << "Cannot write to file: " << e.what() << '\n';
  return -1;
}
catch (const Unsupported_image_extension& e) {
  std::cerr << "Unsupported image extension: " << e.what() << '\n';
  std::fputs("Currently: only ppm output is supported", stderr);
  return -2;
}
catch (const std::exception& e) {
  std::cerr << "Error: " << e.what() << '\n';
  throw e;
}
catch (...) {
  std::fputs("Unknown exception", stderr);
  return -255;
}
