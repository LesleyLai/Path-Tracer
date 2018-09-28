#ifndef TILE_HPP
#define TILE_HPP

#include <cassert>
#include <vector>

#include "color.hpp"

struct Tile {
public:
  Tile() = default;

  Tile(size_t startX, size_t startY, size_t width, size_t height)
      : startX_{startX}, startY_{startY}, width_{width}, height_{height}
  {
    data_.resize(width_ * height_);
  }

  Color at(size_t i, size_t j) const
  {
    assert(i < width_);
    assert(j < height_);
    return data_[j * width_ + i];
  }

  Color& at(size_t i, size_t j)
  {
    assert(i < width_);
    assert(j < height_);
    return data_[j * width_ + i];
  }

  size_t height() const { return height_; }
  size_t width() const { return width_; }
  size_t startX() const { return startX_; }
  size_t startY() const { return startY_; }

private:
  size_t startX_ = 0;
  size_t startY_ = 0;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<Color> data_{};
};

#endif // TILE_HPP
