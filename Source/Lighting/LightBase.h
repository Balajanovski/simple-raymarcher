// 
// Created by Balajanovski on 21/12/2017.
//

#ifndef SIMPLE_RAYTRACER_LIGHT_H
#define SIMPLE_RAYTRACER_LIGHT_H

#include "../Geometry/Vec3f.h"
#include "../Color.h"

class LightBase {
public:
    LightBase(const Vec3f& pos, float ambient, float diffuse, float specular, float intensity, float attenuation, Color color)
            : m_pos(pos), m_ambient(ambient),
              m_diffuse(diffuse), m_specular(specular), m_attenuation(attenuation), m_color(color), m_intensity(intensity) { }
    LightBase() = default;


    virtual Vec3f light_vec() const = 0;

    Vec3f pos() const { return m_pos; }
    void set_pos(const Vec3f& pos) { m_pos = pos; }

    Color ambient() const { return m_color * m_ambient; }
    void set_ambient(float amb) { m_ambient = amb; }

    Color diffuse() const { return m_color * m_diffuse; }
    void set_diffuse(float diffuse) { m_diffuse = diffuse; }

    Color specular() const { return m_color * m_specular; }
    void set_specular(float specular) { m_specular = specular; }

    Color intensity() const {
        return Color(m_intensity, m_intensity, m_intensity);
    }

    void set_intensity(float intensity) { m_intensity = intensity; }

    Color color() const { return m_color; }
    void set_color(Color color) { m_color = color; }

    float attenuation() const { return m_attenuation; }
    void set_attenuation(float attenuation) { m_attenuation = attenuation; }
private:
    Vec3f m_pos;

    float m_ambient;
    float m_diffuse;
    float m_specular;
    float m_attenuation;
    Color m_color;
    float m_intensity;
};


#endif //SIMPLE_RAYTRACER_LIGHT_H
