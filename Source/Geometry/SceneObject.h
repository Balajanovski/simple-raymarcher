// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_SCENEOBJECT_H
#define SIMPLE_RAYTRACER_SCENEOBJECT_H

#include "../Material.h"
#include "Intersection.h"
#include "Vec3f.h"

class SceneObject {
public:
    SceneObject(const Material& material) : m_surface_material(material) { }

    Material surface_material() const { return m_surface_material; }

    virtual Intersection sdf (const Vec3f& position) const = 0;
private:
    Material m_surface_material;
};


#endif //SIMPLE_RAYTRACER_SCENEOBJECT_H
