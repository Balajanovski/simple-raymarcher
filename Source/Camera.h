// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_CAMERA_H
#define SIMPLE_RAYTRACER_CAMERA_H

#include <memory>

#include "Screen.h"
#include "Geometry/Vec3f.h"
#include "Geometry/Ray.h"

class Camera {
public:
    Camera(const Vec3f& camera_pos, const std::shared_ptr<Screen<int>>& grid);

    Ray fire_ray(float x, float y);
private:
    Vec3f m_pos;

    std::shared_ptr<Screen<int>> m_grid;
};

#endif //SIMPLE_RAYTRACER_CAMERA_H
