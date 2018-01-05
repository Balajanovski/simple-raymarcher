// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_RAYTRACER_H
#define SIMPLE_RAYTRACER_RAYTRACER_H

#include "Scene.h"
#include "Camera.h"
#include "PixelBufferBase.h"
#include "Screen.h"

#include "Geometry/Ray.h"
#include "Util/NonCopyable.h"
#include "Color.h"
#include "ConfigManager.h"

#include <utility>

class Raymarcher {
public:
    Raymarcher(std::shared_ptr<Scene>& scene,
               std::shared_ptr<PixelBufferBase>& buffer,
               std::shared_ptr<Screen<int>>& grid)
            : m_scene(scene), m_buffer(buffer), m_grid(grid) {
        epsilon = 2.0f / (m_grid->get_x_max() - m_grid->get_x_min());
    }
    void calculate_frame();
    void calculate_rows(int y_lower_bound, int y_upper_bound, int x_min, int x_max, const ConfigManager& config_manager_instance, size_t num_of_lights);
private:

    std::shared_ptr<Scene> m_scene;
    std::shared_ptr<PixelBufferBase> m_buffer;
    std::shared_ptr<Screen<int>> m_grid;

    void estimate_normal(IN const Vec3f& point, OUT Vec3f& normal);

    void march(IN const Ray& ray, OUT Intersection& output_intersection);

    std::pair<float, float> convert_grid_coords_to_screen_space(int x, int y);
    void phong_contrib_for_light(IN const Color& diffuse, IN const Color &specular, IN float alpha, IN const Vec3f &pos,
                                    IN const Vec3f &eye, IN const LightBase& light, IN float attenuation, OUT Color& output_color);
    void phong_illumination(IN const Material& material, IN const LightBase& light, IN const Vec3f& pos,
                               IN const Vec3f& eye, OUT Color& output_color);

    static constexpr int MAX_MARCHING_STEPS = 256;
    static constexpr int NUM_OF_THREADS = 256;
    float epsilon;
};


#endif //SIMPLE_RAYTRACER_RAYTRACER_H
