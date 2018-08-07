#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "color.hpp"

struct Unsupported_image_extension : public std::invalid_argument {
  explicit Unsupported_image_extension(const char* filename)
      : std::invalid_argument{filename}
  {
  }
};

struct Cannot_write_file : public std::runtime_error {
  explicit Cannot_write_file(const char* filename)
      : std::runtime_error{filename}
  {
  }
};

class Image {
public:
  Image(size_t width, size_t height);

  /**
   * @brief Save the image into a file
   * @param filename with extension
   *
   * Currently only support ppm as extension.
   */
  void saveto(const std::string& filename) const;

  size_t width() const { return width_; }

  size_t height() const { return height_; }

  Color color_at(size_t x, size_t y) const
  {
    bound_checking(x, y);
    return data_[y * width_ + x];
  }

  Color& color_at(size_t x, size_t y)
  {
    bound_checking(x, y);
    return data_[y * width_ + x];
  }

private:
  void bound_checking(size_t x, size_t y) const
  {
    if (x >= width_ || y >= height_) {
      std::stringstream ss;
      ss << "Access image out of index:\n";
      ss << "Input x:" << x << " y:" << y << "\n";
      ss << "width:" << width_ << " height:" << height_ << "\n";
      throw std::out_of_range{ss.str().c_str()};
    }
  }

  size_t width_;
  size_t height_;
  std::vector<Color> data_;
};

#endif // IMAGE_HPP
