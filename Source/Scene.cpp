// 
// Created by Balajanovski on 14/12/2017.
//

#include "Scene.h"

#include <cmath>
#include <ctime>
#include <chrono>

Intersection Scene::sceneSDF(const Vec3f &position) {

    // Use constructive solid geometry to union all the sdfs of the objects
    Intersection minimum_intersection = m_objects[0]->sdf(position);
    for (int i = 1; i < m_objects.size(); ++i) {
        Intersection other_object = m_objects[i]->sdf(position);
        minimum_intersection = min(minimum_intersection, other_object);
    }

    return minimum_intersection;
}

void Scene::iterate(double ticks) {
    //m_lights[0].pos().set_y(sinf(ticks));
}

Scene::Scene()
{
    m_objects.push_back(std::make_shared<Sphere>(Vec3f(0.0f, 0.0f, 0.0f), 0.5f, Material(1.0f, 1.0f, 0.1f, 0.8f, Color{1.0f, 0.0f, 0.0f})));
    m_lights.emplace_back(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(-0.5f, 0.0f, 0.0f).normalize(), 1.0f, 1.0f, 1.0f, 3.0f, Color{1.0f, 1.0f, 1.0f});
    m_objects.push_back(std::make_shared<Sphere>(Vec3f(0.5f, 0.0f, 0.0), 1.0f, Material(1.0f, 1.0f, 0.1f, 0.8f, Color{0.0f, 1.0f, 0.0f})));
}