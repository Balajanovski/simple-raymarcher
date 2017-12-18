// 
// Created by Balajanovski on 14/12/2017.
//

#include "Raymarcher.h"

#include "Geometry/Vec3f.h"
#include "Geometry/Ray.h"
#include "Color.h"

#include <limits>
#include <iostream>

void Raymarcher::calculate_frame() {
    //m_buffer->clear();
    for (float y = -1.0; y < 1.0 + EPSILON; y += EPSILON) {
        for (float x = -1.0; x < 1.0 + EPSILON; x += EPSILON) {

            auto ray = m_camera->fire_ray(x, y);
            float depth = 0;

            for (int i = 0; i < MAX_MARCHING_STEPS; ++i) {

                float distance = m_scene->sceneSDF(ray.march(depth));
                //std::cout << ray.march(depth).x() << " " << ray.march(depth).y() << " " << ray.march(depth).z() << std::endl;

                depth += distance;


                if (distance < EPSILON) {
                    (*m_buffer) << Color{255, 255, 255};
                    break;
                }



                if (depth > RENDER_DISTANCE) {
                    (*m_buffer) << Color{0, 0, 0};
                    break;
                }
            }
        }
    }

}