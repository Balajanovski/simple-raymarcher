// 
// Created by Balajanovski on 14/12/2017.
//

#include "Ray.h"
#include <iostream>

Ray Ray::reflect(Vec3f axis_unit_vec) {
    Vec3f projection = axis_unit_vec * m_direction_unit_vec.dot(axis_unit_vec);
    Vec3f step = projection - m_direction_unit_vec;
    return Ray(m_origin_coord, m_direction_unit_vec + step * 2);
}

Vec3f Ray::march(float dist) const {
    //std::cout << m_ray_point.x() << " " << m_ray_point.y() << " " << m_ray_point.z() << std::endl;
    //std::cout << direction_unit_vec().x() << " " << direction_unit_vec().y() << " " << direction_unit_vec().z() << std::endl;
    return (origin_coord() + (direction_unit_vec() * dist));
}