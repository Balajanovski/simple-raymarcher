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

// This clamp with desaturation algorithm was taken from Bisqwit with his permission
// The original source can be found via the link below:
// https://gist.github.com/bisqwit/6fa30964eacefeea2954e5c42c966114

#define LUMA_COEFFICIENTS      0.29900,  0.58700,  0.11400

void Color::clamp_with_desaturation(int x, int y)
{
    float l = dot(Color(LUMA_COEFFICIENTS));
    //float l = rgb.HorizontalSum() / 3.f; // faster but less accurate
    if(l >= 255.f) {
        set_r(1.0f);
        set_g(1.0f);
        set_b(1.0f);
        return;
    }

    // __builtin_expect is an optimization to the traditional else if statement
    // supported by GNU gcc and LLVM clang.
#if defined(__GNUC__) || defined(__clang__)
    else if(__builtin_expect(l <= 0.0f, false)) {
        set_r(0.0f);
        set_b(0.0f);
        set_g(0.0f);
        return;
    }
#else
    else if(l <= 0.0f) {
        set_r(0.0f);
        set_b(0.0f);
        set_g(0.0f);
        return;
    }
#endif
    else
    {
        float s = 1.0f;
        for(unsigned n = 0; n < 3; ++n) {
            if(m_rgb[n] > 255.f) {
                s = std::min(s, (l - 255.f) / (l - m_rgb[n]));
            }
#if defined(__GNUC__) || defined(__clang__)
            else if(__builtin_expect(m_rgb[n] < 0.0f, false)) {
                s = std::min(s, l           / (l - m_rgb[n]));
            }
#else
            else if(m_rgb[n] < 0.0f) {
                s = std::min(s, l           / (l - m_rgb[n]));
            }
#endif

        }
        if(s != 1.0f) {
            for (int i = 0; i < 3; ++i) {
                m_rgb[i] = (m_rgb[i] - l) * s + l;
            }
        }
    }
    return;
}

void mix(IN const Color& color1, IN const Color& color2, IN float interpolation_factor, OUT Color& mixed_color) {
    mixed_color.set_r(color1.r() * (1 - interpolation_factor) + color2.r() * interpolation_factor);
    mixed_color.set_g(color1.g() * (1 - interpolation_factor) + color2.g() * interpolation_factor);
    mixed_color.set_b(color1.b() * (1 - interpolation_factor) + color2.b() * interpolation_factor);
}