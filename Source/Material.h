// 
// Created by Balajanovski on 21/12/2017.
//

#ifndef SIMPLE_RAYTRACER_MATERIAL_H
#define SIMPLE_RAYTRACER_MATERIAL_H

#include "Color.h"

class Material {
public:
    Material() : m_specular(0.0f), m_diffuse(0.0f), m_ambient(0.0f), m_shininess(0.0f), m_color(0.0f, 0.0f, 0.0f) { }

    Material(float specular, float diffuse, float ambient, float shininess, const Color& color)
        : m_specular(specular), m_diffuse(diffuse), m_ambient(ambient), m_shininess(shininess), m_color(color) { }

    Material(const Material& other)
            : m_specular(other.m_specular), m_diffuse(other.m_diffuse),
              m_ambient(other.m_ambient)  , m_shininess(other.m_shininess), m_color(other.color()) { }

    Material operator=(const Material& rhs) {
        m_specular  = rhs.m_specular;
        m_diffuse   = rhs.m_diffuse;
        m_ambient   = rhs.m_ambient;
        m_shininess = rhs.m_shininess;
        m_color     = rhs.color();

        return *this;
    }

    // Getters
    Color specular()  const { return Vec3f(1.0f, 1.0f, 1.0f) * m_specular;  }
    Color diffuse()   const { return ambient() + (color() * m_diffuse);   }
    Color ambient()   const { return Vec3f(1.0f, 1.0f, 1.0f) * m_ambient;   }
    float shininess()   const { return m_shininess; }
    Color color()     const { return m_color;     }

private:
    float m_specular;
    float m_diffuse;
    float m_ambient;
    float m_shininess;
    Color m_color;
};

namespace YAML {
    template<>
    struct convert<Material> {
        static YAML::Node encode(const Material& rhs) {
            YAML::Node node;
            node["specular"] = rhs.specular();
            node["diffuse"] = rhs.diffuse();
            node["ambient"] = rhs.ambient();
            node["shininess"] = rhs.shininess();
            node["color"] = rhs.color();
            return node;
        }

        static bool decode(const YAML::Node& node, Material& rhs) {
            if(!node.IsMap() || node.size() != 5) {
                return false;
            }

            rhs = Material(node["specular"].as<float>(), node["diffuse"].as<float>(),
                           node["ambient"].as<float>(), node["shininess"].as<float>(), node["color"].as<Color>());
            return true;

        }
    };
}

#endif //SIMPLE_RAYTRACER_MATERIAL_H
