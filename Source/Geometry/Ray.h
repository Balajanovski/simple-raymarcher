// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_RAY_H
#define SIMPLE_RAYTRACER_RAY_H

#include "Vec3f.h"

class Ray {
public:
    Ray() {}
    Ray(Vec3f origin_coord, Vec3f direction_unit_vec)
            : m_origin_coord(origin_coord), m_direction_unit_vec(direction_unit_vec) {}

    Ray reflect(Vec3f axis_unit_vec);

    Vec3f origin_coord() const { return m_origin_coord; }
    Vec3f direction_unit_vec() const { return m_direction_unit_vec; }

    Vec3f march(float dist); // Method to move the ray point along the ray by the distance

private:
    Vec3f m_origin_coord;
    Vec3f m_direction_unit_vec;
};

#endif //SIMPLE_RAYTRACER_RAY_H
