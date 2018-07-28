#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>

#include "image.hpp"
#include "material.hpp"
#include "pathtracer.hpp"
#include "scene.hpp"
#include "sphere.hpp"

void populateScene(Scene& scene)
{
  Material grey{Material::Type::Lambertian, Color(0.5f, 0.5f, 0.5f)};
  Material blue{Material::Type::Lambertian, Color(0.5f, 0.8f, 0.8f)};
  Material bubble{Material::Type::Dielectric, Color(1.f, 1.f, 1.f), 0, 1.1f};
  Material mirror{Material::Type::Metal, Color(0.9f, 0.9f, 0.9f), 0.1f};

  scene.add_object<Sphere>(Vec3f(0, -1000, 0), 1000, grey);
  scene.add_object<Sphere>(Vec3f(1, 2, 0), 1, bubble);
  scene.add_object<Sphere>(Vec3f(-4, 1, 0), 1, blue);
  scene.add_object<Sphere>(Vec3f(4, 1, 0), 1, mirror);

  thread_local auto gen = std::mt19937{std::random_device{}()};
  thread_local std::uniform_real_distribution<float> dis(0.0, 1.0);

  const auto random_color = [&]() { return 0.5f * (1 + dis(gen)); };

  for (int i = -11; i < 11; ++i) {
    for (int j = -11; j < 11; ++j) {
      Vec3f center{i + 0.9f * dis(gen), 0.2f + 0.1f * dis(gen),
                   j + 0.9f * dis(gen)};
      auto choose_mat = dis(gen);

      const auto albedo = Color(random_color(), random_color(), random_color());
      if (choose_mat < 0.7f) {
        Material mat(Material::Type::Lambertian, albedo);
        scene.add_object<Sphere>(center, 0.2f, mat);
      }
      else if (choose_mat < 0.9f) {
        Material mat(Material::Type::Metal, albedo, 0.1f);
        scene.add_object<Sphere>(center, 0.2f, mat);
      }
      else {
        Material mat(Material::Type::Dielectric, albedo, 0, 1.5f);
        scene.add_object<Sphere>(center, 0.2f, mat);
      }
    }
  }
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

  Scene scene{};

  populateScene(scene);

  constexpr auto aspect_ratio = static_cast<float>(width) / height;
  Camera camera{Vec3f{3, 4, 1}, Vec3f{2, 0, 0}, Vec3f{0, 1, 0}, 90.0_deg,
                aspect_ratio};
  auto start = std::chrono::system_clock::now();
  path_tracer.run(scene, camera, image, 5);
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
