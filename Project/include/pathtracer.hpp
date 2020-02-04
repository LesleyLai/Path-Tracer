#ifndef PATHTRACER_HPP
#define PATHTRACER_HPP

#include <cstddef>
#include <random>

class Camera;
class Scene;
class Image;
struct Ray;
struct Color;

#include <indicators/progress_bar.hpp>

class Path_tracer {

public:
  Path_tracer();

  void run(const Scene& scene, const Camera& camera, Image& image,
           size_t sample_per_pixel);

private:
  indicators::ProgressBar progress_bar_{};
};

#endif // PATHTRACER_HPP
