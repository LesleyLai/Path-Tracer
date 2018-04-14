#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <vector>
#include <stdexcept>

struct Unsupported_image_extension : public std::invalid_argument {
    Unsupported_image_extension(const char* filename) : std::invalid_argument{filename} {}
};


struct Cannot_write_file : public std::runtime_error {
    Cannot_write_file(const char* filename) : std::runtime_error{filename} {}
};

class Image {
public:
    Image();

    void saveto(const std::string& filename);

    size_t width() const
    {
        return width_;
    }

    size_t height() const
    {
        return height_;
    }

private:
    size_t width_;
    size_t height_;
};

#endif // IMAGE_HPP
