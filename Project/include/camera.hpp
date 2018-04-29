#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "angle.hpp"
#include "vector.hpp"
#include "ray.hpp"

class Camera
{
public:
//    Camera(Radian fov) {
//        //float half_height =
//    }

    Ray getRay(float u, float v) const {
        return Ray{origin_, lower_left_corner_ + u * horizontal_ + v * vertical_};
    }

private:
    Vec3f origin_ = Vec3f(0.0, 0.0, 0.0);
    Vec3f lower_left_corner_ = Vec3f(-2.0, -1.0, -1.0);
    Vec3f horizontal_ = Vec3f(4.0, 0.0, 0.0);
    Vec3f vertical_ = Vec3f(0.0, 2.0, 0.0);
};

#endif // CAMERA_HPP
