#ifndef PATHTRACER_HPP
#define PATHTRACER_HPP

#include <cstddef>
#include <random>

class Scene;
class Image;
struct Ray;
struct Color;


class Path_tracer
{

public:
    Path_tracer() = default;

    void run(const Scene& scene, Image& image, size_t sample_per_pixel);

private:
    mutable std::mt19937 gen = std::mt19937{ std::random_device{}() }; //Standard mersenne_twister_engine seeded with rd()

    Color trace(const Scene& scene, const Ray& ray, size_t depth = 0) const noexcept;
};

#endif // PATHTRACER_HPP
