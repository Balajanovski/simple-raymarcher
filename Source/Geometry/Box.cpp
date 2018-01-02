// 
// Created by Balajanovski on 2/01/2018.
//

#include "Box.h"

#include <cmath>

Intersection&& Box::sdf(const Vec3f& pos) const {

    auto sample_vector = pos + m_center;
    sample_vector.make_positive();

    Vec3f d = sample_vector - m_box_vector;

    return std::move(Intersection(fminf(fmaxf(d.x(), fmaxf(d.y(), d.z())), 0.0f) + max(d, Vec3f(0, 0, 0)).len(),
                        surface_material(),
                        pos));
}