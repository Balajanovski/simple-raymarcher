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
    Sphere(const Vec3f& center, float radius, const Material& surface_material);

    Vec3f center()        const { return m_center;           }
    float radius()        const { return m_radius;           }
    float radius2()       const { return m_radius2;          }

    virtual void sdf(IN const Vec3f& position, OUT Intersection& output_intersection) const override;

private:
    Vec3f m_center;
    float m_radius, m_radius2; // The sphere's radius and radius^2
};


#endif //SIMPLE_RAYTRACER_SPHERE_H
