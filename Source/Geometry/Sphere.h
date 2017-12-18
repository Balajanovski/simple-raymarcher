// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_SPHERE_H
#define SIMPLE_RAYTRACER_SPHERE_H

#include "Vec3f.h"
#include "Ray.h"
#include "../Color.h"
#include "SceneObject.h"

class Sphere : public SceneObject {
public:
    Sphere(const Vec3f& center, float radius, const Color& surface_color);

    Vec3f center() { return m_center; }
    float radius() { return m_radius; }
    float radius2() { return m_radius2; }
    Color surface_color() { return m_surface_color; }
private:
    Vec3f m_center;
    float m_radius, m_radius2; // The sphere's radius and radius^2
    Color m_surface_color;
};


#endif //SIMPLE_RAYTRACER_SPHERE_H
