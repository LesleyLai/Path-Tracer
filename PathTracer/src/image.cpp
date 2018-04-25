#include <fstream>
#include <regex>

#include "image.hpp"

constexpr int floatColorTo255(double color) {
    return static_cast<int>(255.99 * color);
}

Image::Image(size_t width, size_t height)
    : width_(width), height_(height), data_(width*height) {}

void Image::saveto(const std::string& filename) const
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
    for (index_t j = height_ - 1; j >= 0; --j) {
        for (index_t i = 0; i < width_; ++i) {
            const auto color = color_at(i, j);

            int red = floatColorTo255(std::sqrt(color.r));
            int green = floatColorTo255(std::sqrt(color.g));
            int blue = floatColorTo255(std::sqrt(color.b));

            file << red << ' ' << green << ' ' << blue << '\n';
        }
    }
}




