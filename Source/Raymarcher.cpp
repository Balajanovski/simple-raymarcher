// 
// Created by Balajanovski on 14/12/2017.
//

#include "Raymarcher.h"

#include "Geometry/Vec3f.h"
#include "Geometry/Vec4f.h"
#include "Geometry/Ray.h"
#include "Color.h"
#include "Constants.h"
#include "ConfigManager.h"

#include <cmath>
#include <iostream>

// Uses the gradient of the SDF to estimate the normal on the surface
// Much more efficient than calculus
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

Intersection&& Raymarcher::march(const Ray &ray) {
    Vec3f position;
    Vec3f scaled;

    float total    = 0.0f;
    for (int step = 0; step < MAX_MARCHING_STEPS; ++step) {
        scaled = ray.march(total);
        position = ConfigManager::instance().get_camera()->pos() + scaled;
        auto intersection = m_scene->sceneSDF(position);

        total += intersection.distance();

        // Hits an object
        if (intersection.distance() < epsilon) {
            return Intersection(total, intersection.material(), position);
        }

        // Does not hit an object
        if (intersection.distance() > Constants::MAX_RENDER_DISTANCE) {
            return Intersection(Constants::MAX_RENDER_DISTANCE, Constants::BACKGROUND_MATERIAL, position);
        }
    }
}

std::pair<float, float> Raymarcher::convert_grid_coords_to_screen_space(int x, int y) {
    std::pair<float, float> screen_space_coords;

    screen_space_coords.first  = static_cast<float>(x) / (m_grid->get_x_max() - m_grid->get_x_min()) * 2 - 1.0f;
    screen_space_coords.second = static_cast<float>(y) / (m_grid->get_y_max() - m_grid->get_y_min()) * 2 - 1.0f;

    return screen_space_coords;
}

Color&& Raymarcher::phong_contrib_for_light(const Vec3f &diffuse, const Vec3f &specular, float alpha, const Vec3f &pos,
                                          const Vec3f &eye, const LightBase& light, float attenuation) {
    Vec3f N = estimate_normal(pos);
    Vec3f L = light.light_vec();
    Vec3f V = (eye - pos).normalize();
    Vec3f R = (Vec3f(0.0f, 0.0f, 0.0f) - L).reflect(N);

    float dotLN = L.dot(N);
    float dotRV = R.dot(V);

    if (dotLN < 0.0) {
        // Light not visible
        return Vec3f(0.0, 0.0, 0.0);
    }

    if (dotRV < 0.0) {
        return (light.intensity() * (diffuse * dotLN)) * attenuation;
    }
    return (light.intensity() * (diffuse * dotLN + specular * powf(dotRV, alpha))) * attenuation;
}

Color&& Raymarcher::phong_illumination(const Material& material, const LightBase& light, const Vec3f &pos,
                                     const Vec3f &eye) {
    float attenuation = 1.0f / light.attenuation();

    Color color = (light.ambient() * material.ambient()) * attenuation;

    color += phong_contrib_for_light(material.diffuse().to_vector(), material.specular().to_vector(),
                                     material.shininess(), pos, eye, light, attenuation);

    return std::move(color);
}

void Raymarcher::calculate_frame() {
    for (int y = m_grid->get_y_min(); y < m_grid->get_y_max(); ++y) {
        for (auto x = m_grid->get_x_min(); x < m_grid->get_x_max(); ++x) {
            Ray view_dir = ConfigManager::instance().get_camera()->fire_ray(convert_grid_coords_to_screen_space(x, y));

            // March ray till an intersection is found
            // If no intersection is found the BACKGROUND_MATERIAL is returned with the MAX_RENDER_DISTANCE
            // These are declared in Constants.h

            Intersection intersection = march(view_dir);

            Color pixel_color = Color{0, 0, 0};

            size_t num_of_lights = ConfigManager::instance().get_amount_of_lights();
            for (int i = 0; i < num_of_lights; ++i) {
                // Calculate ambient light
                auto light = ConfigManager::instance().get_light(i);

                auto this_light_color = phong_illumination(intersection.material(), *light, intersection.pos(), ConfigManager::instance().get_camera()->pos());

                pixel_color += this_light_color;

            }

            pixel_color.clamp_with_desaturation();
            (*m_buffer).add_to_buffer(x, y, std::move(pixel_color));

        }
    }
}