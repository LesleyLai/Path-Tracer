#include <iostream>

#include "image.hpp"

int main()
try {
    Image image(200, 100);
    const auto width = image.width(), height = image.height();
    for (index_t j = 0; j < height; ++j) {
        for (index_t i = 0; i < width; ++i) {
            auto r = static_cast<float>(i) / width;
            auto g = static_cast<float>(j) / height;
            auto b = 0.2f;
            image.color_at(i, j) = Color{r,g,b};
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

