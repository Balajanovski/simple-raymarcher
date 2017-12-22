// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_CAMERA_H
#define SIMPLE_RAYTRACER_CAMERA_H

#include <memory>
#include <utility>

#include "Screen.h"
#include "Geometry/Vec3f.h"
#include "Geometry/Ray.h"

class Camera {
public:
    Camera(const Vec3f& camera_pos);

    Ray fire_ray(const std::pair<float, float>& coords);

    Vec3f pos() const { return m_pos; }
private:
    Vec3f m_pos;
};

#endif //SIMPLE_RAYTRACER_CAMERA_H
