// 
// Created by Balajanovski on 21/12/2017.
//

#ifndef SIMPLE_RAYTRACER_MATERIAL_H
#define SIMPLE_RAYTRACER_MATERIAL_H

#include "Color.h"

class Material {
public:
    Material(float specular, float diffuse, float ambient, float shininess, const Color& color)
        : m_specular(specular), m_diffuse(diffuse), m_ambient(ambient), m_shininess(shininess), m_color(color) { }

    Material(const Material& other)
            : m_specular(other.specular()), m_diffuse(other.diffuse()),
              m_ambient(other.ambient())  , m_shininess(other.shininess()), m_color(other.color()) { }

    Material operator=(const Material& rhs) {
        m_specular  = rhs.specular();
        m_diffuse   = rhs.diffuse();
        m_ambient   = rhs.ambient();
        m_shininess = rhs.shininess();
        m_color     = rhs.color();

        return *this;
    }

    // Getters
    float specular()  const { return m_specular;  }
    float diffuse()   const { return m_diffuse;   }
    float ambient()   const { return m_ambient;   }
    float shininess() const { return m_shininess; }
    Color color()     const { return m_color;     }

private:
    float m_specular;
    float m_diffuse;
    float m_ambient;
    float m_shininess;
    Color m_color;
};

#endif //SIMPLE_RAYTRACER_MATERIAL_H
