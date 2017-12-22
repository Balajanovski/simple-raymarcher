// 
// Created by Balajanovski on 14/12/2017.
//

#include "Raymarcher.h"

#include "Geometry/Vec3f.h"
#include "Geometry/Ray.h"
#include "Color.h"

#include <cmath>
#include <iostream>

const Material Raymarcher::BACKGROUND_MATERIAL = Material(0, 0, 0, 0, Color{0, 0, 0});

Vec3f Raymarcher::estimate_normal(Vec3f point) {

    return (Vec3f(
            m_scene->sceneSDF(Vec3f(point.x() + epsilon, point.y(), point.z())).distance() -
                    m_scene->sceneSDF(Vec3f(point.x() - epsilon, point.y(), point.z())).distance(),
            m_scene->sceneSDF(Vec3f(point.x(), point.y() + epsilon, point.z())).distance() -
                    m_scene->sceneSDF(Vec3f(point.x(), point.y() - epsilon, point.z())).distance(),
            m_scene->sceneSDF(Vec3f(point.x(), point.y(), point.z()  + epsilon)).distance() -
                    m_scene->sceneSDF(Vec3f(point.x(), point.y(), point.z() - epsilon)).distance()
    )).normalize();
}

Intersection Raymarcher::march(const Ray &ray) {
    Vec3f position;
    Vec3f scaled;

    float total    = 0.0f;
    for (int step = 0; step < MAX_MARCHING_STEPS; ++step) {
        scaled = ray.march(total);
        position = m_camera->pos() + scaled;
        auto intersection = m_scene->sceneSDF(position);

        total += intersection.distance();

        // Hits an object
        if (intersection.distance() < epsilon) {
            return Intersection(total, intersection.material());
        }

        // Does not hit an object
        if (intersection.distance() > MAX_RENDER_DISTANCE) {
            return Intersection(MAX_RENDER_DISTANCE, BACKGROUND_MATERIAL);
        }
    }
}

std::pair<float, float> Raymarcher::convert_grid_coords_to_screen_space(int x, int y) {
    std::pair<float, float> screen_space_coords;

    screen_space_coords.first  = static_cast<float>(x) / (m_grid->get_x_max() - m_grid->get_x_min()) * 2 - 1.0f;
    screen_space_coords.second = static_cast<float>(y) / (m_grid->get_y_max() - m_grid->get_y_min()) * 2 - 1.0f;

    return screen_space_coords;
}

void Raymarcher::calculate_frame() {
    //m_buffer->clear();
    for (auto y = m_grid->get_y_min(); y < m_grid->get_y_max(); ++y) {
        for (auto x = m_grid->get_x_min(); x < m_grid->get_x_max(); ++x) {
            auto intersection = march(m_camera->fire_ray(convert_grid_coords_to_screen_space(x, y)));

            // Hits an object
            if (intersection.distance() < MAX_RENDER_DISTANCE) {
                (*m_buffer) << intersection.material().color();
            }

            // Does not hit an object
            else {
                (*m_buffer) << Color{0.0f, 0.0f, 0.0f};
            }
        }
    }

}