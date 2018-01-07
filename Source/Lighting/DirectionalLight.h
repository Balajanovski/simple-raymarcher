// 
// Created by Balajanovski on 26/12/2017.
//

#ifndef SIMPLE_RAYTRACER_DIRECTIONALLIGHT_H
#define SIMPLE_RAYTRACER_DIRECTIONALLIGHT_H

#include "LightBase.h"
#include "../Geometry/Vec3f.h"

// Directional lights don't have attenuation so set it as 1.0f which makes the light not attenuate
class DirectionalLight : public LightBase {
public:
    DirectionalLight(const Vec3f& pos, const Vec3f& light_dir, float ambient,
                     float diffuse, float specular, float intensity, Color color)
            : LightBase(pos, ambient, diffuse, specular, intensity, 1.0f, color), m_light_direction(light_dir) { }
    DirectionalLight() = default;

    virtual Vec3f light_vec(const Vec3f& end_of_light_ray_pos) const override { return m_light_direction; }
    void set_light_direction(const Vec3f& dir) { m_light_direction = dir; }

private:
    Vec3f m_light_direction;
};


#endif //SIMPLE_RAYTRACER_DIRECTIONALLIGHT_H
