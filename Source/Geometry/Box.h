// 
// Created by Balajanovski on 2/01/2018.
//

#ifndef SIMPLE_RAYTRACER_BOX_H
#define SIMPLE_RAYTRACER_BOX_H

#include "SceneObject.h"
#include <cmath>

// Created for the menger sponge fractal
#define box_sdf(position, center, box_vector, output_intersection_distance)                                             \
    {                                                                                                                   \
                                                                                                                        \
        auto sample_vector = (position) + (center);                                                                     \
        sample_vector.make_positive();                                                                                  \
                                                                                                                        \
        Vec3f d = sample_vector - (box_vector);                                                                         \
                                                                                                                        \
        output_intersection_distance = (std::fmin(std::fmax(d.x(),                                                      \
                                fmax(d.y(), d.z())), 0.0f) + max(d, Vec3f(0, 0, 0)).len());                             \
    }                                                                                                                   \

class Box : public SceneObject {
public:
    Box(const Vec3f& center, const Vec3f& vec, const Material& material)
            : SceneObject(material), m_box_vector(vec), m_center(center) {  }
    virtual void sdf (IN const Vec3f& position, OUT Intersection& output_intersection) const override;
private:
    Vec3f m_box_vector;
    Vec3f m_center;
};


#endif //SIMPLE_RAYTRACER_BOX_H
