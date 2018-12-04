// 
// Created by Balajanovski on 2/01/2018.
//

#include "Box.h"

void Box::sdf(IN const Vec3f& position, OUT Intersection& output_intersection) const {

    float intersection_distance;
    box_sdf(position, m_center, m_box_vector, intersection_distance);

    output_intersection = (Intersection(intersection_distance,
                        surface_material(),
                        position));
    return;
}