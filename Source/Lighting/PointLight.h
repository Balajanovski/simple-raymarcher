// 
// Created by Balajanovski on 7/01/2018.
//

#ifndef SIMPLE_RAYTRACER_POINTLIGHT_H
#define SIMPLE_RAYTRACER_POINTLIGHT_H

#include "LightBase.h"

class PointLight : public LightBase {
public:
    PointLight(const Vec3f& pos, float ambient,
                     float diffuse, float specular, float intensity, float attenuation, Color color)
            : LightBase(pos, ambient, diffuse, specular, intensity, attenuation, color) { }
    virtual Vec3f light_vec(const Vec3f& end_of_light_ray_pos) const override;
};


#endif //SIMPLE_RAYTRACER_POINTLIGHT_H
