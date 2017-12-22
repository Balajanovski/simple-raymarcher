// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_COLOR_H
#define SIMPLE_RAYTRACER_COLOR_H

class Color {
public:
    Color(float r, float g, float b);
    Color() { m_rgb[0] = m_rgb[1] = m_rgb[2] = 0; }

    float r() const { return m_rgb[0]; }
    float g() const { return m_rgb[1]; }
    float b() const { return m_rgb[2]; }

    void clamp_with_desaturation();
    void clamp();
private:
    float m_rgb[3];
};


#endif //SIMPLE_RAYTRACER_COLOR_H
