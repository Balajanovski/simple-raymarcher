// 
// Created by Balajanovski on 23/12/2017.
//

#ifndef SIMPLE_RAYTRACER_VEC4F_H
#define SIMPLE_RAYTRACER_VEC4F_H

class Vec4f {
public:
    Vec4f(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) { }
    Vec4f() : m_x(0), m_y(0), m_z(0), m_w(0) { }

    float x() const { return m_x; }
    float y() const { return m_y; }
    float z() const { return m_z; }
    float w() const { return m_w; }

    Vec4f operator+(const Vec4f& rhs) const;
    Vec4f operator-(const Vec4f& rhs) const;
    Vec4f operator*(float k) const;
    Vec4f operator/(float k) const;

    float len() const;
    Vec4f normalize() const;
    float dot(const Vec4f& rhs) const;
private:
    float m_x, m_y, m_z, m_w;
};


#endif //SIMPLE_RAYTRACER_VEC4F_H
