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

    Vec3f&& estimate_normal(Vec3f point);

    Intersection&& march(const Ray& ray);

    std::pair<float, float> convert_grid_coords_to_screen_space(int x, int y);
    Color&& phong_contrib_for_light(const Color& diffuse, const Color& specular, float alpha, const Vec3f& pos, const Vec3f& eye,
                                  const LightBase& light, float attenuation);
    Color&& phong_illumination(const Material& material, const LightBase& light, const Vec3f &pos,
                             const Vec3f &eye);

    static constexpr int MAX_MARCHING_STEPS = 256;
    static constexpr int NUM_OF_THREADS = 64;
    float epsilon;
};


#endif //SIMPLE_RAYTRACER_RAYTRACER_H
