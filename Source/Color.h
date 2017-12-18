// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_COLOR_H
#define SIMPLE_RAYTRACER_COLOR_H

class Color {
public:
    Color(float r, float g, float b);
    Color() : m_r(0), m_g(0), m_b(0) { }

    float r() const { return m_r; }
    float g() const { return m_g; }
    float b() const { return m_b; }
private:
    float m_r, m_g, m_b;
};


#endif //SIMPLE_RAYTRACER_COLOR_H
