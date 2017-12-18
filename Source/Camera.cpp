// 
// Created by Balajanovski on 15/12/2017.
//

#include <stdexcept>

#include "Camera.h"
#include "Geometry/Vec3f.h"

Camera::Camera(const Vec3f& camera_pos, const std::shared_ptr<Screen<int>> &grid) : m_pos(camera_pos), m_grid(grid) { }

Ray Camera::fire_ray(float x, float y) {
    /*
    if (x < m_grid->get_x_min() || x > m_grid->get_x_max()) {
        throw std::runtime_error("x argument in Camera::fire_ray is outside the bounds of the grid");
    }
    if (y < m_grid->get_y_min() || y > m_grid->get_y_max()) {
        throw std::runtime_error("y argument in Camera::fire_ray is outside hte bounds of the grid");
    }
     */

    Vec3f ray_direction = ((Vec3f(x, 0, 0) +
                            Vec3f(0, y, 0) +
                            Vec3f(0, 0, 1))).normalize();

    return Ray(m_pos, ray_direction);
}