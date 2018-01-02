// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_COLOR_H
#define SIMPLE_RAYTRACER_COLOR_H

#include "Geometry/Vec3f.h"

#include <yaml-cpp/node/node.h>

class Color {
public:
    Color(float r, float g, float b);
    Color(const Vec3f& vector);
    Color() { m_rgb[0] = m_rgb[1] = m_rgb[2] = 0; }

    float r() const { return m_rgb[0]; }
    float g() const { return m_rgb[1]; }
    float b() const { return m_rgb[2]; }

    void set_r(float r) { m_rgb[0] = r; }
    void set_g(float g) { m_rgb[1] = g; }
    void set_b(float b) { m_rgb[2] = b; }

    // Vector operations
    Color operator+(const Color& rhs) const;
    Color operator-(const Color& rhs) const;
    Color operator*(float k) const;
    Color operator*(const Color& rhs) const;
    Color operator/(float k) const;

    void operator+=(const Color& rhs);
    void operator-=(const Color& rhs);
    void operator*=(float k);
    void operator*=(const Color& rhs);
    void operator/=(float k);

    float dot(const Color& rhs) const;
    Color cross(const Color& rhs ) const;

    void clamp_with_desaturation();
    void clamp();
    Vec3f to_vector() { return Vec3f(r(), g(), b()); }

private:
    float m_rgb[3];

    static constexpr float Pr = 0.299;
    static constexpr float Pg = 0.587;
    static constexpr float Pb = 0.114;
};

namespace YAML {
    template<>
    struct convert<Color> {
        static YAML::Node encode(const Color& rhs) {
            YAML::Node node;
            node["R"] = static_cast<float>(rhs.r());
            node["G"] = static_cast<float>(rhs.g());
            node["B"] = static_cast<float>(rhs.b());
            return node;
        }

        static bool decode(const YAML::Node& node, Color& rhs) {
            if(!node.IsMap() || node.size() != 3) {
                return false;
            }

            if (node["R"].as<float>() > 1.0f || node["G"].as<float>() > 1.0f || node["B"].as<float>() > 1.0f ||
                node["R"].as<float>() < 0.0f || node["G"].as<float>() < 0.0f || node["B"].as<float>() < 0.0f) {
                throw std::runtime_error("config file syntax error: Color nodes must be between 0.0 and 1.0");
            }

            rhs.set_r(node["R"].as<float>());
            rhs.set_g(node["G"].as<float>());
            rhs.set_b(node["B"].as<float>());
            return true;
        }
    };
}

#endif //SIMPLE_RAYTRACER_COLOR_H
