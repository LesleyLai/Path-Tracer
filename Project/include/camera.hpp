#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vector.hpp"
#include "ray.hpp"

class Camera
{
public:
    Ray getRay(double u, double v) const {
        return Ray{origin_, lower_left_corner_ + u * horizontal_ + v * vertical_};
    }

private:
    Vec3d origin_ = Vec3d(0.0, 0.0, 0.0);
    Vec3d lower_left_corner_ = Vec3d(-2.0, -1.0, -1.0);
    Vec3d horizontal_ = Vec3d(4.0, 0.0, 0.0);
    Vec3d vertical_ = Vec3d(0.0, 2.0, 0.0);
};

#endif // CAMERA_HPP
