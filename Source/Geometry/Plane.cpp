// 
// Created by Balajanovski on 29/12/2017.
//

#include "Plane.h"
#include <cstdio>

Intersection&& Plane::sdf(const Vec3f &pos) const {
    //printf("%f\n", pos.dot(Vec3f(m_normal.x(), m_normal.y(), m_normal.z())) + m_normal.w());
    return std::move(Intersection(pos.dot(Vec3f(m_normal.x(), m_normal.y(), m_normal.z())) + m_normal.w(), surface_material(), pos));
}