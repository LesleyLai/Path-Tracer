#include <cmath>
#include <fstream>
#include <regex>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "image.hpp"

using byte = unsigned char;
constexpr byte floatColorTo255(float color) {
    return static_cast<byte>(255.99f * color);
}

Image::Image(size_t width, size_t height)
    : width_(width), height_(height), data_(width*height) {}

void Image::saveto(const std::string& filename) const
{
	/*std::regex ppm {R"(.*\.ppm$)"};
    if (!std::regex_match(filename, ppm)) {
        throw Unsupported_image_extension{filename.c_str()};
    }*/

	std::regex png {R"(.*\.png$)"};
	if (!std::regex_match(filename, png)) {
	throw Unsupported_image_extension{filename.c_str()};
	}
	
	std::vector<byte> buffer;
	buffer.reserve(data_.size() * 3);
    for (auto i = data_.crbegin(), end = data_.crend(); i != end; ++i) {
		byte red = floatColorTo255(std::sqrt(i->r));
		byte green = floatColorTo255(std::sqrt(i->g));
		byte blue = floatColorTo255(std::sqrt(i->b));
		//auto color: data_
		buffer.push_back(red);
		buffer.push_back(green);
		buffer.push_back(blue);
	}
	stbi_write_png(filename.c_str(), width_, height_, 3, reinterpret_cast<void*>(buffer.data()), width_ * 3);

	/*
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
	*/
}




