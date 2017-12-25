// 
// Created by Balajanovski on 15/12/2017.
//

#include <stdexcept>

#include "Camera.h"
#include "Geometry/Vec3f.h"

Camera::Camera(const Vec3f& camera_pos) : m_pos(camera_pos) { }

Ray Camera::fire_ray(const std::pair<float, float>& coords) {

    if (coords.first < -1.0f || coords.first > 1.0f) {
        throw std::runtime_error("x argument in Camera::fire_ray is outside the screen of the grid");
    }
    if (coords.second < -1.0f || coords.second > 1.0f) {
        throw std::runtime_error("y argument in Camera::fire_ray is outside hte screen of the grid");
    }


    Vec3f ray_direction = ((Vec3f(coords.first, 0, 0) +
                            Vec3f(0, coords.second, 0) +
                            Vec3f(0, 0, 1))).normalize();

    return Ray(m_pos, ray_direction);
}