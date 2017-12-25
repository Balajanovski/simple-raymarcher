// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_RAYTRACER_H
#define SIMPLE_RAYTRACER_RAYTRACER_H

#include "Scene.h"
#include "Camera.h"
#include "Pixel_Stream_Base.h"
#include "Screen.h"

#include "Geometry/Ray.h"
#include "Util/NonCopyable.h"

#include <utility>

class Raymarcher {
public:
    Raymarcher(Scene* scene,
               Camera* camera,
               Pixel_Stream_Base* buffer,
               Screen<int>* grid)
            : m_scene(scene), m_camera(camera), m_buffer(buffer), m_grid(grid) {
        epsilon = 2.0f / (m_grid->get_x_max() - m_grid->get_x_min());
    }
    void calculate_frame();
private:

    Scene* m_scene;
    Camera* m_camera;
    Pixel_Stream_Base* m_buffer;
    Screen<int>* m_grid;

    Vec3f estimate_normal(Vec3f point);

    Intersection march(const Ray& ray);

    std::pair<float, float> convert_grid_coords_to_screen_space(int x, int y);

    static constexpr int MAX_MARCHING_STEPS = 50;
    static constexpr float MAX_RENDER_DISTANCE = 300;
    static const Material BACKGROUND_MATERIAL;
    float epsilon;
};


#endif //SIMPLE_RAYTRACER_RAYTRACER_H
