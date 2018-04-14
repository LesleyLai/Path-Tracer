#include <fstream>
#include <regex>

#include "image.hpp"

Image::Image() : width_(200), height_(100) {}

using index_t = std::ptrdiff_t;

constexpr int floatColorTo255(double color) {
    return static_cast<int>(255.99 * color);
}

void Image::saveto(const std::string& filename)
{
    std::regex ppm {R"(.*\.ppm$)"};
    if (!std::regex_match(filename, ppm)) {
        throw Unsupported_image_extension{filename.c_str()};
    }

    std::ofstream file {filename};
    if (!file.is_open()) {
        throw Cannot_write_file{filename.c_str()};
    }

    file << "P3\n" << width_ << ' ' << height_ << "\n255\n";
    for (index_t j = 0; j < height_; ++j) {
        for (index_t i = 0; i < width_; ++i) {
            auto r = static_cast<double>(i) / width_;
            auto g = static_cast<double>(j) / height_;
            auto b = 0.2;

            int red = floatColorTo255(r);
            int green = floatColorTo255(g);
            int blue = floatColorTo255(b);

            file << red << ' ' << green << ' ' << blue << '\n';
        }
    }
}




