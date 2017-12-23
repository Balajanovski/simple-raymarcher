// 
// Created by Balajanovski on 14/12/2017.
//

#include "Sphere.h"

Sphere::Sphere(const Vec3f &center, float radius, const Material& surface_material)
        : m_center(center), m_radius(radius), m_radius2(radius * radius), SceneObject(surface_material) { }

Intersection Sphere::sdf(const Vec3f &position) const {
    return Intersection(position.len() - radius(), surface_material(), position);
}