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
    Path_tracer path_tracer;

    const auto mat1 = std::make_unique<Material>(0.5, Material::Type::Lambertian);
    const auto mat2 = std::make_unique<Material>(0.9, Material::Type::Reflect);

    Scene scene;
    scene.add_object<Sphere>(Vec3d(0,0,-1), 0.5, mat2.get());
    scene.add_object<Sphere>(Vec3d(-2, 0,-2), 0.5, mat2.get());
    scene.add_object<Sphere>(Vec3d(2, 0,-2), 0.5, mat2.get());
    scene.add_object<Sphere>(Vec3d(0,-100.5,-1), 100, mat1.get());

    path_tracer.run(scene);

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

