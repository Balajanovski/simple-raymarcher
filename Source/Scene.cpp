// 
// Created by Balajanovski on 14/12/2017.
//

#include "Scene.h"

#include <iostream>

float Scene::sceneSDF(const Vec3f &position) {
    //std::cout << m_sphere.radius() << std::endl;
    return position.normalize().len() - m_sphere.radius();
}

Scene::Scene() : m_sphere(Vec3f(50.0, 0.0, 0.0), 0.5, Color{255, 255, 255}) {

}