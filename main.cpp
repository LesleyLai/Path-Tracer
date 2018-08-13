#include <chrono>
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
const Lambertian grey{Color(0.5f, 0.5f, 0.5f)};
const Emission light{Color(4.f, 4.f, 4.f)};
} // namespace

Scene create_scene()
{
  std::vector<std::unique_ptr<Hitable>> objects;
  std::vector<std::unique_ptr<Material>> materials;

  objects.push_back(
      std::make_unique<Sphere>(Point3f(0, -1000, 0), 1000.f, grey));
  objects.push_back(std::make_unique<Sphere>(Point3f(0, 2, 0), 2, grey));
  objects.push_back(std::make_unique<Sphere>(Point3f(0, 7, 0), 2, light));
  objects.push_back(
      std::make_unique<Rect_XY>(Point2f(1, 3), Point2f(3, 5), -2, light));

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
    std::cout << s / 60 << "min " << s % 60 << "s\n";
  }
}

int main() try {
  using namespace std::chrono;

  Path_tracer path_tracer;

  constexpr int width = 800, height = 600;
  Image image(width, height);

  const auto scene = create_scene();

  constexpr auto aspect_ratio = static_cast<float>(width) / height;
  Camera camera{{13, 2, 3}, {0, 0, 0}, {0, 1, 0}, 45.0_deg, aspect_ratio};
  auto start = std::chrono::system_clock::now();
  path_tracer.run(scene, camera, image, 50);
  auto end = std::chrono::system_clock::now();

  std::cout << "elapsed time: ";
  print_elapse_time(end - start);

  std::string filename{"test.png"};
  image.saveto(filename);
  std::cout << "Save image to " << filename << '\n';

  return 0;
}
catch (const Cannot_write_file& e) {
  std::cerr << "Cannot write to file: " << e.what() << '\n';
  return -1;
}
catch (const Unsupported_image_extension& e) {
  std::cerr << "Unsupported image extension: " << e.what() << '\n';
  std::cerr << "Currently: only ppm output is supported\n";
  return -2;
}
catch (const std::exception& e) {
  std::cerr << "Error: " << e.what();
  throw e;
}
catch (...) {
  std::cerr << "Unknown exception";
  return -255;
}
