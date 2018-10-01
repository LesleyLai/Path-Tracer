#ifndef PATHTRACER_HPP
#define PATHTRACER_HPP

#include <cstddef>
#include <random>

class Camera;
class Scene;
class Image;
struct Ray;
struct Color;

class Path_tracer {

public:
  Path_tracer() = default;

  void run(const Scene& scene, const Camera& camera, Image& image,
           size_t sample_per_pixel);
};

#endif // PATHTRACER_HPP
