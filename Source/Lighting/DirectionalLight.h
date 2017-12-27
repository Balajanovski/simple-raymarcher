// 
// Created by Balajanovski on 26/12/2017.
//

#ifndef SIMPLE_RAYTRACER_DIRECTIONALLIGHT_H
#define SIMPLE_RAYTRACER_DIRECTIONALLIGHT_H

#include "LightBase.h"
#include "../Geometry/Vec3f.h"

class DirectionalLight : public LightBase {
public:
    DirectionalLight(const Vec3f& pos, const Vec3f& light_dir, float ambient,
                     float diffuse, float specular, float intensity, float attenuation, Color color)
            : LightBase(pos, ambient, diffuse, specular, intensity, attenuation, color), m_light_direction(light_dir) { }
    DirectionalLight() = default;

    virtual Vec3f light_vec() const override { return m_light_direction; }
    void set_light_direction(const Vec3f& dir) { m_light_direction = dir; }

private:
    Vec3f m_light_direction;
};


#endif //SIMPLE_RAYTRACER_DIRECTIONALLIGHT_H
