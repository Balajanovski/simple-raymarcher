// 
// Created by Balajanovski on 2/01/2018.
//

#ifndef SIMPLE_RAYTRACER_BOX_H
#define SIMPLE_RAYTRACER_BOX_H

#include "SceneObject.h"

class Box : public SceneObject {
public:
    Box(const Vec3f& center, const Vec3f& vec, const Material& material)
            : SceneObject(material), m_box_vector(vec), m_center(center) {  }
    virtual Intersection&& sdf(const Vec3f& pos) const override;
private:
    Vec3f m_box_vector;
    Vec3f m_center;
};


#endif //SIMPLE_RAYTRACER_BOX_H
