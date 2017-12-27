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

#include <utility>

class Raymarcher {
public:
    Raymarcher(Scene* scene,
               PixelBufferBase* buffer,
               Screen<int>* grid)
            : m_scene(scene), m_buffer(buffer), m_grid(grid) {
        epsilon = 2.0f / (m_grid->get_x_max() - m_grid->get_x_min());
    }
    void calculate_frame();
private:

    Scene* m_scene;
    PixelBufferBase* m_buffer;
    Screen<int>* m_grid;

    Vec3f estimate_normal(Vec3f point);

    Intersection march(const Ray& ray);

    std::pair<float, float> convert_grid_coords_to_screen_space(int x, int y);
    Color phong_contrib_for_light(const Vec3f& diffuse, const Vec3f& specular, float alpha, const Vec3f& pos, const Vec3f& eye,
                                  const LightBase& light);
    Color phong_illumination(const Material& material, const LightBase& light, const Vec3f &pos,
                             const Vec3f &eye);

    static constexpr int MAX_MARCHING_STEPS = 50;
    float epsilon;
};


#endif //SIMPLE_RAYTRACER_RAYTRACER_H
