#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "angle.hpp"
#include "vector.hpp"
#include "ray.hpp"

class Camera
{
public:
    /**
     * @brief Camera
     * @param fov
     * @param aspect Aspect ratio of the screen
     */
    constexpr Camera(Radian fov, float aspect) noexcept {
        const float half_height = std::tan(fov.value());
        const float half_width = aspect * half_height;
        lower_left_corner_ = Vec3f(-half_width, -half_height, -1);
        horizontal_ = Vec3f(2 * half_width, 0, 0);
        vertical_ = Vec3f(0, 2 * half_height, 0);
    }

    Ray getRay(float u, float v) const noexcept {
        return Ray{origin_, lower_left_corner_ + u * horizontal_ + v * vertical_};
    }

private:
    Vec3f origin_ = Vec3f(0.0, 0.0, 0.0);
    Vec3f lower_left_corner_;
    Vec3f horizontal_;
    Vec3f vertical_;
};

#endif // CAMERA_HPP
