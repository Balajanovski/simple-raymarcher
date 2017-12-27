// 
// Created by Balajanovski on 26/12/2017.
//

#ifndef SIMPLE_RAYTRACER_CONSTANTS_H
#define SIMPLE_RAYTRACER_CONSTANTS_H

#include "Material.h"

namespace Constants {
    static constexpr float MAX_RENDER_DISTANCE = 300;
    static const Material BACKGROUND_MATERIAL = Material(0, 0, 0, 0, Color{0.0f, 0.0f, 0.0f});
}

#endif //SIMPLE_RAYTRACER_CONSTANTS_H
