#include <chrono>
#include <stdexcept>
#include <iostream>
#include <memory>

#include "pathtracer.hpp"
#include "image.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "sphere.hpp"

int main()
try {
    using namespace std::chrono;

    Path_tracer path_tracer;

    auto blue = std::make_unique<Lambertian>(Color(0.5f, 0.8f, 0.8f));
    auto pink = std::make_unique<Lambertian>(Color(0.8f, 0.2f, 0.2f));
    auto bronze = std::make_unique<Metal>(Color(0.8f, 0.5f, 0.2f) / 2.0f, 0.2);
    auto mirror = std::make_unique<Metal>(Color(0.9f, 0.9f, 0.9f), 0.1);

    Scene scene {Camera{}};
    scene.add_object<Sphere>(Vec3d(0,0,-1), 0.5, bronze.get());
    scene.add_object<Sphere>(Vec3d(-2, 0,-2), 0.5, blue.get());
    scene.add_object<Sphere>(Vec3d(2, 0,-2), 0.5, mirror.get());
    scene.add_object<Sphere>(Vec3d(0,-100.5,-1), 100, pink.get());

    Image image(200, 100);

    auto start = std::chrono::system_clock::now();
    path_tracer.run(scene, image);
    auto end = std::chrono::system_clock::now();

    std::cout << "elapsed time: ";
    auto elapsed_time = end-start;
    if (elapsed_time < 1s) {
        std::cout << duration_cast<milliseconds>(elapsed_time).count() << "ms\n";
    } else if (elapsed_time < 1min) {
        std::cout << duration_cast<seconds>(elapsed_time).count() << "s\n";
    } else {
        auto s = duration_cast<seconds>(elapsed_time).count();
        std::cout << s / 60 << "min " << s % 60 << "s";
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

