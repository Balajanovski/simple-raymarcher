// 
// Created by Balajanovski on 22/01/2018.
//

#include "Menger.h"
#include "Box.h"

void Menger::sdf(IN const Vec3f& position, OUT Intersection& output_intersection) const {
    auto menger_material = surface_material();

    float menger_distance = 0.0f;
    box_sdf(position, m_center, Vec3f(1.0f, 1.0f, 1.0f), menger_distance);

    Color color = menger_material.color();

    float s = 1.0;
    for(int m = 0; m < m_iterations; ++m)
    {
        Vec3f a = (((position + m_center) * s) % 2.0f) - 1.0f;
        s *= 3.0;

        Vec3f r = abs((abs(a) * 3.0f) - 1.0f);

        float da = std::max(r.x(),r.y());
        float db = std::max(r.y(),r.z());
        float dc = std::max(r.z(),r.x());
        float c = (std::min(da, std::min(db,dc)) - 1.0f) / s;

        if(c > menger_distance)
        {
            menger_distance = c;
            color = Color(0.2f * da * db * dc, (1.0f + static_cast<float>(m)) / 4.0f, 0.0f);
        }
    }

    // Generate a mixed color based on the menger fractal as well as its material color
    Color mixed_color;
    mix(color, menger_material.color(), 0.5f, mixed_color);


    output_intersection = Intersection(menger_distance,
                                       Material(menger_material.float_specular(),
                                                menger_material.float_diffuse(),
                                                menger_material.float_ambient(),
                                                menger_material.shininess(),
                                                mixed_color), position);
    return;
}