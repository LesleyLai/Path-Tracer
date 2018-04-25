#include <iostream>
#include <limits>
#include <random>
#include <memory>

#include "camera.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "image.hpp"
#include "sphere.hpp"
#include "scene.hpp"

constexpr size_t samples_count = 200;

std::mt19937 gen(std::random_device{}()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_real_distribution<> dis(-1, 1);

Vec3d random_in_unit_circle() {
    Vec3d p;
    do {
        p = Vec3d(dis(gen), dis(gen), dis(gen));
    } while (p.length_square() >= 1);
    return p;
}


constexpr size_t max_recursion = 5;
Color colorof(const Scene& scene, const Ray& ray, size_t recursion_count = max_recursion)
{
	if (recursion_count == 0) {
		return Color{ 0, 0, 0 };
	}

	constexpr double inf = std::numeric_limits<double>::infinity();
	constexpr double damping = 0.5;

    if (auto hit = scene.intersect_at(ray, 0, inf)) {
        Vec3d target = hit->point + hit->normal + random_in_unit_circle();

        return damping * colorof(scene, Ray{hit->point, target - hit->point}, recursion_count-1);
    }

    const auto unit_direction = ray.direction / ray.direction.length();
    const auto t = static_cast<float>(0.5 * (unit_direction.y + 1));
    return (1.f - t) * Color{1,1,1} + t * Color(0.5f, 0.7f, 1);
}

int main()
try {
    Image image(200, 100);

    // Camera
    Camera camera;

    Scene scene {};
    scene.add_object<Sphere>(Vec3d(0,0,-1), 0.5);
    scene.add_object<Sphere>(Vec3d(0,-100.5,-1), 100);

    const auto width = image.width(), height = image.height();

    std::mt19937 gen(std::random_device{}()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (index_t j = 0; j < height; ++j) {
        for (index_t i = 0; i < width; ++i) {
            Color c;
            for (index_t sample = 0; sample < samples_count; ++sample) {
                const double u = (i + dis(gen)) / width;
                const double v = (j + dis(gen)) / height;

                const auto r = camera.getRay(u, v);
                c += colorof(scene, r);
            }
            c /= static_cast<float>(samples_count);
            image.color_at(i, j) = c;            
        }
        std::cout << (j / static_cast<double>(height) * 100) << "%\n" << std::flush;
    }

    std::string filename {"test.ppm"};
    image.saveto(filename);
    std::cout << "Save image to " << filename << '\n';
    return 0;
} catch (const Cannot_write_file& e) {
    std::cerr << "Cannot write to file: " << e.what() << '\n';
    return -1;
} catch (const Unsupported_image_extension& e) {
    std::cerr << "Unsupported image extension: " << e.what() << '\n';
    std::cerr << "Currently: only ppm output is supported\n";
    return -2;
}  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what();
    throw e;
}  catch (...) {
    std::cerr << "Unknown exception";
    return -255;
}

