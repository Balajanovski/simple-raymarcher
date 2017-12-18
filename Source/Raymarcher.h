// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_RAYTRACER_H
#define SIMPLE_RAYTRACER_RAYTRACER_H

#include "Scene.h"
#include "Camera.h"
#include "Pixel_Stream_Base.h"
#include "Screen.h"

#include "Util/NonCopyable.h"

#include <memory>

class Raymarcher : public Util::NonCopyable {
public:
    Raymarcher(const std::shared_ptr<Scene>& scene,
               const std::shared_ptr<Camera>& camera,
               const std::shared_ptr<Pixel_Stream_Base>& buffer,
               const std::shared_ptr<Screen<int>>& grid)
            : m_scene(scene), m_camera(camera), m_buffer(buffer), m_grid(grid) { }
    void calculate_frame();
private:
    std::shared_ptr<Scene> m_scene;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Pixel_Stream_Base> m_buffer;
    std::shared_ptr<Screen<int>> m_grid;

    static constexpr int MAX_MARCHING_STEPS = 50;
    static constexpr float RENDER_DISTANCE = 300;
    static constexpr float EPSILON = 0.05;
};


#endif //SIMPLE_RAYTRACER_RAYTRACER_H
