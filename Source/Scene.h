// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_SCENE_H
#define SIMPLE_RAYTRACER_SCENE_H

#include "Light.h"

#include "Geometry/Sphere.h"
#include "Geometry/SceneObject.h"
#include "Geometry/Vec3f.h"
#include "Geometry/Intersection.h"

#include <vector>
#include <memory>

class Scene {
public:
    Intersection sceneSDF(const Vec3f& position);

    Light get_light(int index) const { return m_lights[index]; }
    size_t get_num_of_lights() const { return m_lights.size(); }

    void iterate(double ticks);

    Scene();
private:
    std::vector<std::shared_ptr<SceneObject>> m_objects;
    std::vector<Light> m_lights;
};


#endif //SIMPLE_RAYTRACER_SCENE_H
