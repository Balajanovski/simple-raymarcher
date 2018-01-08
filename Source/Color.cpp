// 
// Created by Balajanovski on 14/12/2017.
//

#include "Color.h"

#include <cmath>

Color::Color(float r, float g, float b) {
    m_rgb[0] = r;
    m_rgb[1] = g;
    m_rgb[2] = b;
}

Color::Color(const Vec3f &vector) {
    m_rgb[0] = vector.x();
    m_rgb[1] = vector.y();
    m_rgb[2] = vector.z();
}

Color Color::operator+(const Color &rhs) const {
    return Color(r() + rhs.r(), g() + rhs.g(), b() + rhs.b());
}

Color Color::operator-(const Color &rhs) const {
    return Color(r() - rhs.r(), g() - rhs.g(), b() - rhs.b());
}

Color Color::operator*(float k) const {
    return Color(r() * k, g() * k, b() * k);
}

Color Color::operator*(const Color &rhs) const {
    return Color(r() * rhs.r(), g() * rhs.g(), b() * rhs.b());
}

Color Color::operator/(float k) const {
    return Color(r() / k, g() / k, b() / k);
}

void Color::operator+=(const Color &rhs) {
    *this = *this + rhs;
}

void Color::operator-=(const Color &rhs) {
    *this = *this - rhs;
}

void Color::operator*=(float k) {
    *this = *this * k;
}

void Color::operator*=(const Color &rhs) {
    *this = *this * rhs;
}

void Color::operator/=(float k) {
    *this = *this / k;
}


float Color::dot(const Color &rhs) const {
    return (r() * rhs.r()) + (g() * rhs.g()) + (b() * rhs.b());
}

Color Color::cross(const Color &rhs) const {
    return Color(g() * rhs.b() - b() * rhs.g(),
                 b() * rhs.r() - r() * rhs.b(),
                 r() * rhs.g()- g() * rhs.r());
}

inline float clamp_value(float value) {
    value = (value < 0.0f) ? 0.0f : value;
    value = (value > 1.0f) ? 1.0f : value;

    return value;
}

inline double calculate_luma(float *rgb)
{
    return rgb[0] * 0.2126 + rgb[1] * 0.7152 + rgb[2] * 0.0722;
}

void Color::clamp() {
    for (int i = 0; i < 3; ++i) {
        m_rgb[i] = clamp_value(m_rgb[i]);
    }
}

#define dmin(a, b) (((a) < (b)) ? (a) : (b))

void Color::clamp_with_desaturation() {
    double luma = calculate_luma(m_rgb),
           sat  = 1.0;

    if (luma > 1.0) {
        m_rgb[0] = m_rgb[1] = m_rgb[2] = 1.0;
        return;
    }

    if (luma < 0.0) {
        m_rgb[0] = m_rgb[1] = m_rgb[2] = 0.0;
        return;
    }

    for (int i = 0; i < 3; ++i) {
        if (m_rgb[i] > 1.0) {
            sat = dmin(sat, (luma - 1.0) / (luma - m_rgb[i]));
        }
        else if (m_rgb[i] < 0.0) {
            sat = dmin(sat, luma / (luma - m_rgb[i]));
        }
    }

    if (sat != 1.0) {
        for (int i = 0; i < 3; ++i) {
            m_rgb[i] = (m_rgb[i] - luma) * sat + luma;
            m_rgb[i] = clamp_value(m_rgb[i]);
        }
    }

}

void mix(IN const Color& color1, IN const Color& color2, IN float interpolation_factor, OUT Color& mixed_color) {
    mixed_color.set_r(color1.r() * (1 - interpolation_factor) + color2.r() * interpolation_factor);
    mixed_color.set_g(color1.g() * (1 - interpolation_factor) + color2.g() * interpolation_factor);
    mixed_color.set_b(color1.b() * (1 - interpolation_factor) + color2.b() * interpolation_factor);
}