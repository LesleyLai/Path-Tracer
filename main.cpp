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

    auto pink = std::make_unique<Lambertian>(Color(0.8f, 0.2f, 0.2f));
    auto blue = std::make_unique<Lambertian>(Color(0.5f, 0.8f, 0.8f));
    auto glass = std::make_unique<Dielectric>(Color(1.f, 1.f, 1.f), 8);
    auto mirror = std::make_unique<Metal>(Color(0.9f, 0.9f, 0.9f), 0.1);

    constexpr int width = 200, height = 100;
    constexpr auto aspect_ratio = static_cast<float>(width) / height;

    Image image(width, height);

    Scene scene {Camera{30.0_deg, aspect_ratio}};
    scene.add_object<Sphere>(Vec3f(0,0,-1), 0.5, glass.get());
    scene.add_object<Sphere>(Vec3f(-2, 0,-2), 0.5, blue.get());
    scene.add_object<Sphere>(Vec3f(2, 0,-2), 0.5, mirror.get());
    scene.add_object<Sphere>(Vec3f(0,-100.5,-1), 100, pink.get());


    auto start = std::chrono::system_clock::now();
    path_tracer.run(scene, image, 800);
    auto end = std::chrono::system_clock::now();

    std::cout << "elapsed time: ";
    auto elapsed_time = end-start;
    if (elapsed_time < 1s) {
        std::cout << duration_cast<milliseconds>(elapsed_time).count() << "ms\n";
    } else if (elapsed_time < 1min) {
        std::cout << duration_cast<seconds>(elapsed_time).count() << "s\n";
    } else {
        auto s = duration_cast<seconds>(elapsed_time).count();
        std::cout << s / 60 << "min " << s % 60 << "s\n";
    }

    std::string filename {"test.png"};
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

