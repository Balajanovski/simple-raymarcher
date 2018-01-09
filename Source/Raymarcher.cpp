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
#include <thread>

const Color Raymarcher::FOG_COLOR = {0.0f, 0.0f, 0.0f};

// Uses the gradient of the SDF to estimate the normal on the surface
// Much more efficient than calculus
void Raymarcher::estimate_normal(IN const Vec3f& point, OUT Vec3f& normal) {

    Intersection x_upper, x_lower,
                 y_upper, y_lower,
                 z_upper, z_lower;

    m_scene->sceneSDF(Vec3f(point.x() + epsilon, point.y(), point.z()), x_upper);
    m_scene->sceneSDF(Vec3f(point.x() - epsilon, point.y(), point.z()), x_lower);

    m_scene->sceneSDF(Vec3f(point.x(), point.y() + epsilon, point.z()), y_upper);
    m_scene->sceneSDF(Vec3f(point.x(), point.y() - epsilon, point.z()), y_lower);

    m_scene->sceneSDF(Vec3f(point.x(), point.y(), point.z() + epsilon), z_upper);
    m_scene->sceneSDF(Vec3f(point.x(), point.y(), point.z() - epsilon), z_lower);

    normal = (Vec3f(
            x_upper.distance() -
                    x_lower.distance(),

            y_upper.distance() -
                    y_lower.distance(),

            z_upper.distance() -
                    z_lower.distance()
    )).normalize();
    return;
}

void Raymarcher::march(IN const Ray& ray, OUT Intersection& output_intersection) {
    Vec3f position;
    Vec3f scaled;

    float total    = 0.0f;
    for (int step = 0; step < MAX_MARCHING_STEPS; ++step) {
        scaled = ray.march(total);
        position = ConfigManager::instance().get_camera()->pos() + scaled;

        Intersection intersection;
        m_scene->sceneSDF(position, intersection);

        total += intersection.distance();

        // Hits an object
        if (intersection.distance() < epsilon) {
            output_intersection = Intersection(total, intersection.material(), position);
            return;
        }

        // Does not hit an object
        if (intersection.distance() > Constants::MAX_RENDER_DISTANCE) {
            output_intersection = Intersection(Constants::MAX_RENDER_DISTANCE, Constants::BACKGROUND_MATERIAL, position);
            return;
        }
    }

    output_intersection = Intersection(Constants::MAX_RENDER_DISTANCE, Constants::BACKGROUND_MATERIAL, position);
    return;
}

std::pair<float, float> Raymarcher::convert_grid_coords_to_screen_space(int x, int y) {
    std::pair<float, float> screen_space_coords;

    screen_space_coords.first  = static_cast<float>(x) / (m_grid->get_x_max() - m_grid->get_x_min()) * 2 - 1.0f;
    screen_space_coords.second = static_cast<float>(y) / (m_grid->get_y_max() - m_grid->get_y_min()) * 2 - 1.0f;

    return screen_space_coords;
}

void Raymarcher::phong_contrib_for_light(IN const Color& diffuse, IN const Color &specular_color, IN float alpha, IN const Vec3f& pos,
                                          IN const Vec3f &eye, IN const LightBase& light, IN float attenuation, OUT Color& output_color) {
    Vec3f N;
    estimate_normal(pos, N);
    Vec3f L = light.light_vec(pos);
    Vec3f camera_dir = (eye - pos).normalize();
    Vec3f R = (Vec3f(0.0f, 0.0f, 0.0f) - L).reflect(N);

    float dotLN = L.dot(N);
    float dotRV = R.dot(camera_dir);

    if (dotLN < 0.0) {
        // Light not visible
        output_color = Color{0.0f, 0.0f, 0.0f};
        return;
    }

    if (dotRV < 0.0) {
        output_color = ((light.intensity() * (diffuse * dotLN)) * attenuation);
        return;
    }

    Vec3f half_direction = (L.normalize() + camera_dir).normalize();
    float specular = std::pow(std::fmax(half_direction.dot(N), 0.0), 16.0);

    // Blinn - phong calculation
    output_color = ((light.intensity() * ((diffuse) * dotLN +
            (specular_color) * std::pow(dotRV, alpha) * specular)) * attenuation);
    return;
}

void Raymarcher::phong_illumination(IN const Material& material, IN const LightBase& light, IN const Vec3f& pos,
                                     IN const Vec3f& eye, OUT Color& output_color) {
    float attenuation = 1.0f / light.attenuation();

    Color color = (light.ambient() * material.ambient()) * attenuation;

    Color phong_contrib_for_light_output;
    phong_contrib_for_light(material.diffuse(), material.specular(),
                                     material.shininess(), pos, eye, light, attenuation, phong_contrib_for_light_output);
    color += phong_contrib_for_light_output;

    output_color = color;
    return;
}

void Raymarcher::apply_fog(IN const Color& color, IN float distance, OUT Color& resultant_color) {
    float fog_amount = 1.0 - std::pow(M_E, -distance * 0.1);
    mix(color, FOG_COLOR, fog_amount, resultant_color);
}

void Raymarcher::calculate_rows(int y_lower_bound, int y_upper_bound, int x_min, int x_max, const ConfigManager& config_manager_instance, size_t num_of_lights) {
    for (auto y = y_lower_bound; y < y_upper_bound; ++y) {
        for (auto x = x_min; x < x_max; ++x) {
            Ray view_dir = config_manager_instance.get_camera()->fire_ray(convert_grid_coords_to_screen_space(x, y));

            // March ray till an intersection is found
            // If no intersection is found the BACKGROUND_MATERIAL is returned with the MAX_RENDER_DISTANCE
            // These are declared in Constants.h

            Intersection intersection;
            march(view_dir, intersection);

            Color pixel_color = Color{0, 0, 0};

            for (int i = 0; i < num_of_lights; ++i) {
                auto light = config_manager_instance.get_light(i);

                Color this_light_color;
                phong_illumination(intersection.material(), *light, intersection.pos(),
                                   config_manager_instance.get_camera()->pos(), this_light_color);

                pixel_color += this_light_color;

            }

            apply_fog(pixel_color, intersection.distance(), pixel_color);

            pixel_color.clamp_with_desaturation(x, y);

            (*m_buffer).add_to_buffer(x, y, std::move(pixel_color));

        }
    }
}

void Raymarcher::calculate_frame() {
    size_t num_of_lights = ConfigManager::instance().get_amount_of_lights();

    int y_min = m_grid->get_y_min();
    int y_max = m_grid->get_y_max();

    int x_min = m_grid->get_x_min();
    int x_max = m_grid->get_x_max();

    auto& config_manager_instance = ConfigManager::instance();

    // Initialise threads
    std::vector<std::thread> threads;
    int rows_per_thread = (y_max - y_min) / NUM_OF_THREADS;

    // Partition the screen based
    for (int y = y_min; y < y_max; y += rows_per_thread) {
        threads.push_back(std::thread(&Raymarcher::calculate_rows, this,
                                      y, y + rows_per_thread, x_min, x_max,
                                      std::cref(config_manager_instance), num_of_lights));
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }
}