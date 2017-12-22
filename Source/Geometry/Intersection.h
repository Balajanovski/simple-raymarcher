// 
// Created by Balajanovski on 21/12/2017.
//

#ifndef SIMPLE_RAYTRACER_INTERSECTION_H
#define SIMPLE_RAYTRACER_INTERSECTION_H

#include "../Material.h"

// This class is what is returned by the scene sdf
// It is a combination of the distance from the closest
// object and the material of said object

class Intersection {
public:
    Intersection(float distance, const Material& material) : m_distance(distance), m_material(material) { }

    float distance()    const { return m_distance; }
    Material material() const { return m_material; }
private:
    float    m_distance;
    Material m_material;
};


#endif //SIMPLE_RAYTRACER_INTERSECTION_H
