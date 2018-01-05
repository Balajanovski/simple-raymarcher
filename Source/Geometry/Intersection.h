// 
// Created by Balajanovski on 21/12/2017.
//

#ifndef SIMPLE_RAYTRACER_INTERSECTION_H
#define SIMPLE_RAYTRACER_INTERSECTION_H

#include "../Material.h"
#include "Vec3f.h"

// This class is what is returned by the scene sdf
// It is a combination of the distance from the closest
// object and the material of said object

class Intersection {
public:
    Intersection(float distance, const Material& material, const Vec3f& pos)
            : m_distance(distance), m_material(material), m_intersection_pos(pos) { }
    Intersection() = default;

    float    distance() const { return m_distance; }
    Material material() const { return m_material; }
    Vec3f    pos()      const { return m_intersection_pos; }
private:
    float    m_distance;
    Material m_material;
    Vec3f    m_intersection_pos;
};

Intersection min(const Intersection& a, const Intersection& b);
Intersection max(const Intersection& a, const Intersection& b);

#endif //SIMPLE_RAYTRACER_INTERSECTION_H
