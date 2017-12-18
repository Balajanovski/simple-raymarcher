// 
// Created by Balajanovski on 14/12/2017.
//

#include "Sphere.h"

Sphere::Sphere(const Vec3f &center, float radius, const Color &surface_color) : m_center(center), m_radius(radius), m_radius2(radius * radius), m_surface_color(surface_color) { }