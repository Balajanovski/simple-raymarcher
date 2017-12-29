// 
// Created by Balajanovski on 29/12/2017.
//

#ifndef SIMPLE_RAYTRACER_PLANE_H
#define SIMPLE_RAYTRACER_PLANE_H

#include "SceneObject.h"

class Plane : public SceneObject {
public:
    Plane(const Vec3f& normal, float w, const Material& material) :
            SceneObject(material), m_normal(normal), m_w(w) { }
    virtual Intersection sdf(const Vec3f& pos) { }
private:
    Vec3f m_normal;
    float m_w;
};


#endif //SIMPLE_RAYTRACER_PLANE_H
