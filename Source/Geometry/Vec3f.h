// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_VECTOR3_H
#define SIMPLE_RAYTRACER_VECTOR3_H

class Vec3f {
public:
    Vec3f(float x, float y, float z) : m_x(x), m_y(y), m_z(z) { }
    Vec3f() : m_x(0), m_y(0), m_z(0) { }

    float x() const { return m_x; }
    float y() const { return m_y; }
    float z() const { return m_z; }

    Vec3f operator+(const Vec3f& rhs) const;
    Vec3f operator-(const Vec3f& rhs) const;
    Vec3f operator*(float k) const;
    Vec3f operator/(float k) const;

    float len() const;
    Vec3f normalize() const;
    float dot(const Vec3f& rhs) const;
    Vec3f cross(const Vec3f& rhs ) const;
private:
    float m_x, m_y, m_z;
};


#endif //SIMPLE_RAYTRACER_VECTOR3_H
