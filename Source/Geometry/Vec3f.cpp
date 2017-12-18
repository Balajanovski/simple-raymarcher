// 
// Created by Balajanovski on 14/12/2017.
//

#include <cmath>
#include <iostream>
#include "Vec3f.h"

Vec3f Vec3f::operator+(const Vec3f &rhs) const {
    return Vec3f(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());
}

Vec3f Vec3f::operator-(const Vec3f &rhs) const {
    return Vec3f(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
}

Vec3f Vec3f::operator*(float k) const {
    return Vec3f(x() * k, y() * k, z() * k);
}

Vec3f Vec3f::operator/(float k) const {
    return Vec3f(x() / k, y() / k, z() / k);
}

float Vec3f::len() const {
    //std::cout << "x: " << x() << " y: " << y() << " z: " << z() << " len: " << sqrtf((x() * x()) + (y() * y()) + (z() * z())) << std::endl;
    return sqrtf(dot(*this));
}

Vec3f Vec3f::normalize() const {
    if (len() == 0.0) {
        return *this;
    }
    return (*this / len());
}

float Vec3f::dot(const Vec3f &rhs) const {
    return (x() * rhs.x()) + (y() * rhs.y()) + (z() * rhs.z());
}

Vec3f Vec3f::cross(const Vec3f &rhs) const {
    return Vec3f(y() * rhs.z() - z() * rhs.y(),
                   z() * rhs.x() - x() * rhs.z(),
                   x() * rhs.y()- y() * rhs.x());
}