// 
// Created by Balajanovski on 29/12/2017.
//

#ifndef SIMPLE_RAYTRACER_PLANE_H
#define SIMPLE_RAYTRACER_PLANE_H

#include "SceneObject.h"

#include "Vec4f.h"

class Plane : public SceneObject {
public:
    Plane(const Vec4f& normal, const Material& material) :
            SceneObject(material), m_normal(normal.normalize()) { }
    virtual Intersection sdf(const Vec3f& pos) const override;
private:
    Vec4f m_normal;
};


#endif //SIMPLE_RAYTRACER_PLANE_H
