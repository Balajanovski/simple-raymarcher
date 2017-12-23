// 
// Created by Balajanovski on 21/12/2017.
//

#ifndef SIMPLE_RAYTRACER_LIGHT_H
#define SIMPLE_RAYTRACER_LIGHT_H

#include "Geometry/Vec3f.h"
#include "Color.h"

class Light {
public:
    Light(const Vec3f& pos, const Vec3f& dir, float ambient, float diffuse, float specular, float attenuation, Color color)
            : m_pos(pos), m_direction(dir), m_ambient(ambient),
              m_diffuse(diffuse), m_specular(specular), m_attenuation(attenuation), m_color(color) { }

    Vec3f pos() const { return m_pos; }
    void set_pos(const Vec3f& pos) { m_pos = pos; }

    Vec3f dir() const { return m_direction; }
    void set_dir(const Vec3f& dir) { m_direction = dir; }

    Color ambient() const { return m_color * m_ambient; }
    void set_ambient(float amb) { m_ambient = amb; }

    Color diffuse() const { return m_color * m_diffuse; }
    void set_diffuse(float diffuse) { m_diffuse = diffuse; }

    Color specular() const { return m_color * m_specular; }
    void set_specular(float specular) { m_specular = specular; }

    Color color() const { return m_color; }
    void set_color(Color color) { m_color = color; }

    float attenuation() const { return m_attenuation; }
    void set_attenuation(float attenuation) { m_attenuation = attenuation; }
private:
    Vec3f m_pos;
    Vec3f m_direction;

    float m_ambient;
    float m_diffuse;
    float m_specular;
    float m_attenuation;
    Color m_color;
};


#endif //SIMPLE_RAYTRACER_LIGHT_H
