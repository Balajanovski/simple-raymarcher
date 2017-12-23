// 
// Created by Balajanovski on 14/12/2017.
//

#include "Raymarcher.h"

#include "Geometry/Vec3f.h"
#include "Geometry/Vec4f.h"
#include "Geometry/Ray.h"
#include "Color.h"

#include <cmath>
#include <algorithm>

const Material Raymarcher::BACKGROUND_MATERIAL = Material(0, 0, 0, 0, Color{0.0f, 0, 0});

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
            return Intersection(total, intersection.material(), position);
        }

        // Does not hit an object
        if (intersection.distance() > MAX_RENDER_DISTANCE) {
            return Intersection(MAX_RENDER_DISTANCE, BACKGROUND_MATERIAL, position);
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
            Ray view_dir = m_camera->fire_ray(convert_grid_coords_to_screen_space(x, y));
            Intersection intersection = march(view_dir);

            // Hits an object
            if (intersection.distance() < MAX_RENDER_DISTANCE) {
                Color pixel_color = Color{0, 0, 0};

                int num_of_lights = m_scene->get_num_of_lights();
                for (int i = 0; i < num_of_lights; ++i) {
                    // Calculate ambient light
                    auto light = m_scene->get_light(i);

                    Color ambient = intersection.material().ambient() * light.ambient();

                    // Calculate diffuse light
                    Vec3f normal = estimate_normal(intersection.pos());
                    float reflection_dp = std::max(0.0f, normal.dot(light.dir()));
                    Color diffuse = intersection.material().diffuse() * light.diffuse() * reflection_dp;

                    // Calculate specular light
                    // TODO

                    Color specular;
                    Vec3f light_dir_normal = light.dir().normalize();
                    if (normal.dot(Vec3f(0, 0, 0) - light_dir_normal) >= 0.0) {
                        Vec3f reflection_dir = light_dir_normal.reflect(normal);
                        float shine_factor = reflection_dir.dot(view_dir.direction_unit_vec());
                        specular = light.specular() * intersection.material().specular()
                                   * powf(std::max(0.0f, shine_factor), intersection.material().shininess().r());
                    }

                    float attenuation = 1.0f / light.attenuation();

                    Color this_light_color = (ambient * attenuation + diffuse * attenuation + specular * attenuation);
                    this_light_color.clamp();
                    pixel_color += this_light_color;

                }

                (*m_buffer) << std::move(pixel_color);
            }

            // Does not hit an object
            else {
                (*m_buffer) << BACKGROUND_MATERIAL.color();
            }
        }
    }

}