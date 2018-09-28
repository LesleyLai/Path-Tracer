#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "angle.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "vector.hpp"

/**
 * @brief The Camera_sample struct hold all the sample value for a camera to
 * generate a ray
 */
struct Camera_sample {
  Point2f film_pos;
};

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
  Camera(Point3f position, Point3f lookat, Vec3f up, Radian fov,
         float aspect) noexcept
  {
    const float half_height = std::tan(fov.value() / 2);
    const float half_width = aspect * half_height;

    origin_ = position;
    const auto w = normalize(position - lookat);
    const auto u = normalize(cross(up, w));
    const auto v = cross(w, u);

    lower_left_corner_ = origin_ - half_width * u - half_height * v - w;
    horizontal_ = 2 * half_width * u;
    vertical_ = 2 * half_height * v;
  }

  /**
   * @brief Generate a ray by uv coodinate
   */
  Ray get_ray(Camera_sample sample) const noexcept
  {
    const auto u = sample.film_pos.x;
    const auto v = sample.film_pos.y;
    return Ray{origin_,
               lower_left_corner_ + u * horizontal_ + v * vertical_ - origin_};
  }

private:
  Point3f origin_{};
  Point3f lower_left_corner_{};
  Vec3f horizontal_{};
  Vec3f vertical_{};
};

#endif // CAMERA_HPP
