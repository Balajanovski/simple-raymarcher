// 
// Created by Balajanovski on 14/12/2017.
//

#include "Scene.h"

#include <iostream>

Intersection Scene::sceneSDF(const Vec3f &position) {
    return m_sphere.sdf(position);
}

Scene::Scene()
        : m_sphere(Vec3f(0.0, 0.0, 1.0), 0.5f, Material(1.0f, 1.0f, 0.2f, 0.2f, Color{1.0f, 1.0f, 1.0f}))
{

}