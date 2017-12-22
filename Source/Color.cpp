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

inline float clamp_value(float value) {
    value = (value < 0.0f) ? 0.0f : value;
    value = (value > 1.0f) ? 1.0f : value;

    return value;
}

inline double calculate_luma(float *rgb)
{
    return rgb[0] * 0.299 + rgb[1] * 0.587 + rgb[2] * 0.114;
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

    if (luma < 1.0) {
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