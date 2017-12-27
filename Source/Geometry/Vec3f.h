// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_VECTOR3_H
#define SIMPLE_RAYTRACER_VECTOR3_H

#include <yaml-cpp/yaml.h>

class Vec3f {
public:
    Vec3f(float x, float y, float z);
    Vec3f() { data[0] = data[1] = data[2] = 0.0f; }
    Vec3f(const Vec3f& other);

    // Getters
    float x() const { return data[0]; }
    float y() const { return data[1]; }
    float z() const { return data[2]; }

    // Setters
    Vec3f set_x(float x) { data[0] = x; return *this; }
    Vec3f set_y(float y) { data[1] = y; return *this; }
    Vec3f set_z(float z) { data[2] = z; return *this; }

    Vec3f operator+(const Vec3f& rhs) const;
    Vec3f operator-(const Vec3f& rhs) const;
    Vec3f operator*(float k) const;
    Vec3f operator*(const Vec3f& rhs) const;
    Vec3f operator/(float k) const;

    float len() const;
    Vec3f normalize() const;
    float dot(const Vec3f& rhs) const;
    Vec3f cross(const Vec3f& rhs ) const;
    Vec3f reflect(const Vec3f& normal) const;

private:
    float data[3];
};

namespace YAML {
    template<>
    struct convert<Vec3f> {
        static YAML::Node encode(const Vec3f& rhs) {
            YAML::Node node;
            node["X"] = static_cast<float>(rhs.x());
            node["Y"] = static_cast<float>(rhs.y());
            node["Z"] = static_cast<float>(rhs.z());
            return node;
        }

        static bool decode(const YAML::Node& node, Vec3f& rhs) {
            if(!node.IsMap() || node.size() != 3) {
                return false;
            }

            rhs.set_x(node["X"].as<float>());
            rhs.set_y(node["Y"].as<float>());
            rhs.set_z(node["Z"].as<float>());
            return true;
        }
    };
}


#endif //SIMPLE_RAYTRACER_VECTOR3_H
