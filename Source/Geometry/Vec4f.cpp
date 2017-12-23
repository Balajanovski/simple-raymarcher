// 
// Created by Balajanovski on 14/12/2017.
//

#include <cmath>

#include "Vec4f.h"

Vec4f Vec4f::operator+(const Vec4f &rhs) const {
    return Vec4f(x() + rhs.x(), y() + rhs.y(), z() + rhs.z(), w() + rhs.w());
}

Vec4f Vec4f::operator-(const Vec4f &rhs) const {
    return Vec4f(x() - rhs.x(), y() - rhs.y(), z() - rhs.z(), w() - rhs.w());
}

Vec4f Vec4f::operator*(float k) const {
    return Vec4f(x() * k, y() * k, z() * k, w() * k);
}

Vec4f Vec4f::operator/(float k) const {
    return Vec4f(x() / k, y() / k, z() / k, w() / k);
}

float Vec4f::len() const {
    return sqrtf(dot(*this));
}

Vec4f Vec4f::normalize() const {
    if (len() == 0.0) {
        return *this;
    }
    return (*this / len());
}

float Vec4f::dot(const Vec4f &rhs) const {
    return (x() * rhs.x()) + (y() * rhs.y()) + (z() * rhs.z()) + (w() * rhs.w());
}