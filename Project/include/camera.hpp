#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "angle.hpp"
#include "ray.hpp"
#include "vector.hpp"
#include <iostream>

class Camera {
public:
  /**
   * @brief Constructor of a camera
   * @param position The position of the camera
   * @param lookat
   * @param up Direction of up
   * @param fov Field of view of the camera
   * @param aspect Aspect ratio of the screen
   */
  Camera(Vec3f position, Vec3f lookat, Vec3f up, Radian fov,
         float aspect) noexcept
  {
    const float half_height = std::tan(fov.value() / 2);
    const float half_width = aspect * half_height;

    origin_ = position;
    const auto w = unit_vector(position - lookat);
    const auto u = unit_vector(cross(up, w));
    const auto v = cross(w, u);

    lower_left_corner_ = origin_ - half_width * u - half_height * v - w;
    horizontal_ = 2 * half_width * u;
    vertical_ = 2 * half_height * v;
  }

  /**
   * @brief Generate a ray by uv coodinate
   */
  Ray get_ray(float u, float v) const noexcept
  {
    return Ray{origin_,
               lower_left_corner_ + u * horizontal_ + v * vertical_ - origin_};
  }

private:
  Vec3f origin_;
  Vec3f lower_left_corner_;
  Vec3f horizontal_;
  Vec3f vertical_;
};

#endif // CAMERA_HPP
