// 
// Created by Balajanovski on 7/01/2018.
//

#include "PointLight.h"

Vec3f PointLight::light_vec(const Vec3f& end_of_light_ray_pos) const {
    return (pos() - end_of_light_ray_pos).normalize();
}