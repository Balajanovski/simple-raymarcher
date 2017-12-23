// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_VECTOR3_H
#define SIMPLE_RAYTRACER_VECTOR3_H

class Vec3f {
public:
    Vec3f(float x, float y, float z);
    Vec3f() { data[0] = data[1] = data[2] = 0.0f; }

    float x() const { return data[0]; }
    float y() const { return data[1]; }
    float z() const { return data[2]; }

    Vec3f operator+(const Vec3f& rhs) const;
    Vec3f operator-(const Vec3f& rhs) const;
    Vec3f operator*(float k) const;
    Vec3f operator*(const Vec3f& rhs) const;
    Vec3f operator/(float k) const;

    float len() const;
    Vec3f normalize() const;
    float dot(const Vec3f& rhs) const;
    Vec3f cross(const Vec3f& rhs ) const;
    Vec3f reflect(const Vec3f& normal) const;
private:
    float data[3];
};


#endif //SIMPLE_RAYTRACER_VECTOR3_H
