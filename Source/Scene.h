// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_SCENE_H
#define SIMPLE_RAYTRACER_SCENE_H

#include <vector>

#include "Geometry/Sphere.h"
#include "Geometry/Vec3f.h"

class Scene {
public:
    float sceneSDF(const Vec3f& position);

    Scene();
private:
    Sphere m_sphere;
};


#endif //SIMPLE_RAYTRACER_SCENE_H
