#include <iostream>

#include "color.hpp"
#include "ray.hpp"
#include "image.hpp"
#include "sphere.hpp"

Color colorof(const Ray& ray) {
    Sphere sphere{Vec3d(0,0,-1), 0.5};
    if (auto t = sphere.intersect_at(ray)) {
        return Color{1, 0, 0};
    }

    const auto unit_direction = ray.direction / ray.direction.length();
    const auto t = static_cast<float>(0.5 * (unit_direction.y + 1));
    return (1.f - t) * Color{1,1,1} + t * Color(0.5f, 0.7f, 1);
}


int main()
try {
    Image image(200, 100);

    // Camera
    const Vec3d origin(0.0, 0.0, 0.0);
    const Vec3d lower_left_corner(-2.0, -1.0, -1.0);
    const Vec3d horizontal(4.0, 0.0, 0.0);
    const Vec3d vertical(0.0, 2.0, 0.0);


    const auto width = image.width(), height = image.height();
    for (index_t j = 0; j < height; ++j) {
        for (index_t i = 0; i < width; ++i) {
            const double u = static_cast<double>(i) / width;
            const double v = static_cast<double>(j) / height;

            const Ray r {origin, lower_left_corner + u * horizontal + v * vertical};
            image.color_at(i, j) = colorof(r);
        }
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

