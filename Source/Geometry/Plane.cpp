// 
// Created by Balajanovski on 29/12/2017.
//

#include "Plane.h"
#include <cstdio>

void Plane::sdf (IN const Vec3f& position, OUT Intersection& output_intersection) const {
    output_intersection = (Intersection(position.dot(Vec3f(m_normal.x(), m_normal.y(), m_normal.z())) + m_normal.w(),
                                        surface_material(), position));
    return;
}