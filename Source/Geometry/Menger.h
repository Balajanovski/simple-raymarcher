// 
// Created by Balajanovski on 22/01/2018.
//

#ifndef SIMPLE_RAYTRACER_MENGER_H
#define SIMPLE_RAYTRACER_MENGER_H

#include "SceneObject.h"

class Menger : public SceneObject {
public:
    Menger(const Vec3f& center, const Material& material, int iterations)
            : SceneObject(material), m_center(center), m_iterations(iterations) { }
    virtual void sdf (IN const Vec3f& position, OUT Intersection& output_intersection) const override;
private:
    Vec3f m_center;
    Vec3f m_block_size;
    int m_iterations;
};


#endif //SIMPLE_RAYTRACER_MENGER_H
