// 
// Created by Balajanovski on 2/01/2018.
//

#include "Box.h"

#include <cmath>

void Box::sdf(IN const Vec3f& position, OUT Intersection& output_intersection) const {

    auto sample_vector = position + m_center;
    sample_vector.make_positive();

    Vec3f d = sample_vector - m_box_vector;

    output_intersection = (Intersection(std::fmin(std::fmax(d.x(), fmax(d.y(), d.z())), 0.0f) + max(d, Vec3f(0, 0, 0)).len(),
                        surface_material(),
                        position));
    return;
}